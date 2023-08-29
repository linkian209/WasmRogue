
//{{{
void get_misc_link(int linknum, struct filelink *ret)
{
	struct filelink *table = deref_file_ptr(get_w()->desc.misc_links);
	*ret = table[linknum];
}
//}}}
//{{{
void create_companion(int type)
{
	int d[1]; // HACKHACK: Can't put a proper struct on the stack yet, but
	          // this is the same size so it works the same
	get_misc_link(type, d);
	addmonster(d, get_plr()->x, get_plr()->y);
}
//}}}
//{{{
int max(int a, int b)
{
	if(a>b) return a;
	else return b;
}
//}}}
//{{{
int min(int a, int b)
{
	if(a<b) return a;
	else return b;
}
//}}}

#define range(a,b) uchar: a; uchar: b;
#define coord(x, y) uchar: x; uchar: y;
//{{{
#define SEQUENCE_PRIMARY   1
#define SEQUENCE_ITEMS     2
#define SEQUENCE_TABLES    3
#define SEQUENCE_STRINGS   4
#define SEQUENCE_MISC      5
#define SEQUENCE_STSIZES   6
#define SEQUENCE_STDATA    7
#define SEQUENCE_BITBUCKET -1
#define SEQUENCE_TEMP      8
//}}}
m4_divert(SEQUENCE_TABLES)

m4_define({@numStrings@}, 0)

//{{{
m4_define(String,
 {@m4_define({@numStrings@}, m4_eval(numStrings+1))
  m4_define({@DIVERT_RET@}, m4_divnum)
  m4_divert(SEQUENCE_STRINGS){@@}
  splitpoint; export STRING_{@@}numStrings{@@};
  string: $1{@@}; even;
  m4_divert(DIVERT_RET)
  STRING_{@@}numStrings
 @})
//}}}
//{{{
m4_define(Itemstring,
 {@m4_define({@numStrings@}, m4_eval(numStrings+1))
  m4_define({@DIVERT_RET@}, m4_divnum)
  m4_divert(SEQUENCE_STRINGS){@@}
  splitpoint; export STRING_{@@}numStrings{@@};
#ifdef SUPPORT_COLOR
  uchar: 0; uchar: 0;
#endif
  string: $1{@@}; even;
  m4_divert(DIVERT_RET)
  STRING_{@@}numStrings
 @})
//}}}
//{{{
m4_define(BEGIN_JUMPTAB,
 {@m4_define({@tabName@}, $1)
  m4_define({@numTabEntries@}, 1)
  m4_define({@tabFreq@}, 0)
  m4_define({@tabCondition@}, {@$2@})
 @})
//}}}
//{{{
m4_define(JTENTRY,
 {@m4_define({@numTabEntries@}, m4_eval(numTabEntries+1))
  m4_divert(SEQUENCE_TEMP)
  link: $1; // Target
  m4_define({@tabFreq@}, m4_eval(tabFreq+$2))
  uint: tabFreq;
  $3      // Range
 @})
//}}}
//{{{
m4_define(END_JUMPTAB,
 {@m4_divert(SEQUENCE_TABLES)
  splitpoint; even;
  export tabName {@(@} PTR_JUMPTABLE {@)@};
  uint: numTabEntries;
  uint: tabCondition;
  
  link: tabName;
  uint: 0;
  uchar: 1; uchar: 2;  // Impossible condition (min 2, max 1) to prevent generation of self
  m4_undivert(SEQUENCE_TEMP)
 @})
//}}}

m4_define({@numSTabs@}, 0)
m4_define({@sTabPos@}, 0)

//{{{
m4_define(BEGIN_SHUFFLETAB,
 {@m4_define({@tabName@}, $1)
  m4_define({@numTabEntries@}, 0)
  m4_define({@numSTabs@}, m4_eval(numSTabs+1))
 @})
//}}}
//{{{
m4_define(STENTRY,
 {@m4_define({@numTabEntries@}, m4_eval(numTabEntries+1))
  m4_divert(SEQUENCE_STDATA)
  export tabName{@@}_{@@}numTabEntries {@(@} PTR_SHUFFLETAB, sTabPos {@)@};
  m4_define({@sTabPos@}, m4_eval(sTabPos+1))
  link: $1;
 @})
//}}}
//{{{
m4_define(STENTRYSTRING,
 {@m4_define({@numTabEntries@}, m4_eval(numTabEntries+1))
  m4_divert(SEQUENCE_STRINGS)
  export tabName{@@}_{@@}numTabEntries{@@}_string;
  string: $1; even;
  m4_divert(SEQUENCE_STDATA)
  export tabName{@@}_{@@}numTabEntries {@(@} PTR_SHUFFLETAB, sTabPos {@)@};
  m4_define({@sTabPos@}, m4_eval(sTabPos+1))
  link: tabName{@@}_{@@}numTabEntries{@@}_string;
 @})
//}}}
//{{{
m4_define(STENTRYITEM,
 {@m4_define({@numTabEntries@}, m4_eval(numTabEntries+1))
  m4_divert(SEQUENCE_STRINGS)
  export tabName{@@}_{@@}numTabEntries{@@}_string;
#ifdef SUPPORT_COLOR
  uchar: $1; uchar: $1;
#endif
  string: $2; even;
  m4_divert(SEQUENCE_STDATA)
  export tabName{@@}_{@@}numTabEntries {@(@} PTR_SHUFFLETAB, sTabPos {@)@};
  m4_define({@sTabPos@}, m4_eval(sTabPos+1))
  link: tabName{@@}_{@@}numTabEntries{@@}_string;
 @})
//}}}
//{{{
m4_define(END_SHUFFLETAB,
 {@m4_divert(SEQUENCE_STSIZES)
  uint: numTabEntries;
  m4_divert(SEQUENCE_BITBUCKET)
 @})
//}}}

m4_divert(SEQUENCE_TABLES)
export MISC_LINKS;
//{{{
link:MONSTER_SUMMON_SKELETON;
link:MONSTER_SUMMON_ZOMBIE;
link:MONSTER_SUMMON_MUMMY;
link:MONSTER_SUMMON_WRAITH;
link:MONSTER_SUMMON_ANGEL;
link:MONSTER_PET_HORSE;
link:MONSTER_BRIDGE_TROLL;
link:MONSTER_SKELETON;
link:MONSTER_FIREELEMENTAL;
link:MONSTER_VORTEX;
link:MONSTER_WATERELEMENTAL;
link:MONSTER_DRAGON;
link:MONSTER_ZOMBIE;
//}}}
//{{{
#define LINK_SUMMON_SKELETON 0
#define LINK_SUMMON_ZOMBIE   1
#define LINK_SUMMON_MUMMY    2
#define LINK_SUMMON_WRAITH   3
#define LINK_SUMMON_ANGEL    4
#define LINK_PET_HORSE       5
#define LINK_BRIDGE_TROLL    6
#define LINK_SKELETON        7
#define LINK_FIRE_ELEMENTAL  8
#define LINK_VORTEX          9
#define LINK_WATER_ELEMENTAL 10
#define LINK_DRAGON          11
#define LINK_ZOMBIE          12
//}}}

m4_divert(SEQUENCE_STSIZES)
even;
export STSIZES;
m4_divert(SEQUENCE_STDATA)
even;
export STDATA;
