
//{{{
/// @brief Roll up stats for a new character
///
/// A character has, depending on class, a set of base stats, maximum values
/// for each stat, and a number of 'free points' which are randomly added
/// onto the base stats. Rather than distribute points one at a time (which
/// would mean that characters would all average out to be about the same),
/// free points are lumped into chunks of 3 (when possible) and assigned
/// that way, OR given out individually.
///
/// @sa classdesc::base_stat classdesc::max_stat classdesc::free_points
void distribute_attributes(void)
{
	int i;
	int stat;
	int points_remaining;
	int points_chunk;
	struct world *w = get_w();
	
	for(i=0; i<NUM_BASE_STATS; i++)
		w->plr.intrinsic[i] = w->playerclasses[w->plr.class].base_stat[i];
	
	points_remaining = w->playerclasses[w->plr.class].free_points;
	while(points_remaining>0)
	{
		do
		{
			stat = random(NUM_BASE_STATS-1, 0);
		} while(w->playerclasses[w->plr.class].max_stat[stat] <= w->plr.intrinsic[stat]);
		
		if(points_remaining>5)
			points_chunk = 3;
		else
			points_chunk = 1;
		w->plr.intrinsic[stat] += points_chunk;
		points_remaining -= points_chunk;
	}
	for(i=0; i<NUM_BASE_STATS; i++)
		w->plr.maximum[i] = w->plr.intrinsic[i];
}
//}}}
//{{{
/// @brief Give the player experience
///
/// The amount of XP needed to gain a level, when the current level is L, is
/// 25*L*(L+2). Extra experience points past what is needed to gain a level
/// are not counted towards the next level; you can only gain one level at
/// a time. Each point of XP gained is worth one point of score.
void awardXP(uint amt)
{
	ulong xpneeded;
	
	get_w()->plr.xp += amt;
	
	// If sufficient experience, gain a level.
	xpneeded = (25*(get_w()->plr.level+2)*get_w()->plr.level);
	
	if(get_w()->plr.xp > xpneeded) {
		message(gettext("You gained a level!"));
		get_w()->plr.level += 1;
		get_w()->plr.xp = 0;
		update_player();
	}
	
	get_w()->plr.score += amt;
}
//}}}
//{{{
void plr_regenerate(int turns)
{
	uint partialhpsperhp;
	uint partialppsperpp;
	struct world *w = get_w();
	
	// Apply draining
	if(w->plr.extrinsic[STAT_FLAGS] & STAT_FLAG_DRAIN)
	{
		if(w->plr.pps > 0) {
			message(gettext("You feel the Amulet sucking your energy away."));
			w->plr.pps--;
		} else {
			message(gettext("You feel the Amulet sucking your life away."));
			plr_takedamage(1, gettext("Killed by the Amulet of Yendor"));
		}
	} else {
		// Regenerate hit points
		partialhpsperhp = 150+10*w->plr.level;
		w->plr.partialhps += (w->plr.hps_max+10) * turns;
		w->plr.hps += w->plr.partialhps / partialhpsperhp;
		w->plr.hps += w->plr.extrinsic[STAT_REGEN];
		w->plr.partialhps-=(w->plr.partialhps/partialhpsperhp)*partialhpsperhp;
		if( w->plr.hps > w->plr.hps_max )
			w->plr.hps = w->plr.hps_max;
		
		// Regenerate power points
		partialppsperpp = 155+10*w->plr.level;
		w->plr.partialpps += (w->plr.pps_max+w->plr.extrinsic[STAT_MANA])*turns;
		w->plr.pps += w->plr.partialpps / partialppsperpp;
		w->plr.pps += w->plr.extrinsic[STAT_PPREGEN];
		w->plr.partialpps-=(w->plr.partialpps/partialppsperpp)*partialppsperpp;
		if( w->plr.pps > w->plr.pps_max )
			w->plr.pps = w->plr.pps_max;
	}
}
//}}}
//{{{
/// Take @a amt of damage. If fatal, die with #cause_of_death shown.
void plr_takedamage(int amt, char *cause_of_death)
{
	struct world *w = get_w();
	
	amt = max( amt - w->plr.extrinsic[STAT_PV], max(amt/4, 1) );
	w->plr.hps -= amt;
	w->interrupt = 1;
	
		// If no hit points and not numb, die.
	if( w->plr.hps <= 0 &&
	    !(w->plr.extrinsic[STAT_FLAGS] & STAT_FLAG_NUMB) )
	{
		die(cause_of_death);
	}
}
//}}}
//{{{
void boost_max_stat(int stat, int amt)
{
	get_w()->plr.maximum[stat] += amt;
	get_w()->plr.intrinsic[stat] = get_w()->plr.maximum[stat];
	update_player();
}
//}}}

//{{{
void begin_tutorial(void)
{
	int ii;
}
//}}}
//{{{
void begin_game(void)
{
	if(get_w()->plr.class == CLASS_TUTORIAL) {
		begin_tutorial();
	} else {
		UI_Dialog_Default(gettext(
"After the Creation, the cruel god Moloch rebelled against the authority of \
Marduk the Creator. Moloch stole from Marduk the most powerful of all the \
artifacts of the gods, the Amulet of Yendor, and he hid it in the dark \
cavities of Gehennom, the Under World, from whence an agent of Loki took it \
and gained standing among the gods. Over time, Loki became cruel and the \
other gods covetted his power. Loki hid the Amulet deep in the earth to keep \
it from them.\n\
You seek possession of the Amulet, to wield, give or destroy it."
		));
	}
}
//}}}

//{{{
void become_knight(void)
{
	get_w()->plr.class = CLASS_KNIGHT;
	boost_max_stat(STAT_STRENGTH, 2);
}
//}}}

//{{{
int attempt_lich_transformation(void)
{
	int ii=0;
	
	message(gettext("You begin the spell."));
	
	// Turn off hunger timer (because that would be a very cruel way to
	// interrupt the spell)
	get_plr()->extrinsic[STAT_DIGESTION] = 0;
	
	get_w()->interrupt = 0;
	for(ii=0; ii<100; ii++) {
		timepass(1);
		if(get_w()->interrupt) {
			message(gettext("The spell is interrupted."));
			die(gettext("Didn't quite become undead."));
			return 0;
		}
	}
	
	message(gettext("The spell is complete!"));
	
	get_plr()->class = CLASS_LICH;
	get_plr()->intrinsic[STAT_MANA] += 4;
	get_plr()->intrinsic[STAT_REGEN] += 1;
	get_plr()->intrinsic[STAT_PPREGEN] += 1;
	get_plr()->intrinsic[STAT_DIGESTION] = 0;
	update_player();
	
	return 1;
}
//}}}

