/* appearance */
static const int sloppyfocus        = 1;  /* focus follows mouse */
static const unsigned int borderpx  = 1;  /* border pixel of windows */
static const float rootcolor[]      = {0.3, 0.3, 0.3, 1.0};
static const float bordercolor[]    = {0.5, 0.5, 0.5, 1.0};
static const float focuscolor[]     = {1.0, 0.0, 0.0, 1.0};

/* tagging */
static const char *tags[] = {
    // 1 = web      2 = tmux        3 = code
    "\ufa9e",       "\uf120",       "\ue62b",
    // 4 = comms    5 = office      6 = media
    "\uf868",       "\uf718",       "\uf001",
    // 7 = fs       8 = backup1     9 = backup2
    "\uf114",       "\uf9e4",       "\uf0e3"
};

static const Rule rules[] = {
	/* app_id     title       tags mask     isfloating   monitor */
	/* examples:
	{ "Gimp",     NULL,       0,            1,           -1 },
	{ "firefox",  NULL,       1 << 8,       0,           -1 },
	*/
};

/* layout(s) */
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* monitors
 * The order in which monitors are defined determines their position.
 * Non-configured monitors are always added to the left. */
const double mfact = 0.55;
static const MonitorRule monrules[] = {
	/* name       mfact nmaster scale layout       rotate/reflect x y */
	/* example of a HiDPI laptop monitor:
	{ "eDP-1",    0.5,  1,      2,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
	*/
	/* defaults */
	{ NULL,       mfact,1,      1,    &layouts[0], WL_OUTPUT_TRANSFORM_NORMAL, 0, 0 },
};

/* keyboard */
static const struct xkb_rule_names xkb_rules = {
	/* can specify fields: rules, model, layout, variant, options */
	/* example:
	.options = "ctrl:nocaps",
	*/
    .layout = "us",
    .options = "caps:backspace,compose:ralt"
};

static const int repeat_rate = 25;
static const int repeat_delay = 600;

/* Trackpad */
static const int tap_to_click = 1;
static const int natural_scrolling = 0;

#ifndef MODKEY
#define MODKEY WLR_MODIFIER_LOGO
#endif
#define TAGKEYS1(KEY,SKEY,TAG) \
    { MODKEY,                    KEY,            toggleview,      {.ui = 1 << TAG} }, \
    { MODKEY|WLR_MODIFIER_CTRL,  KEY,            view,            {.ui = 1 << TAG} }, \
    { MODKEY|WLR_MODIFIER_SHIFT, SKEY,           tag,             {.ui = 1 << TAG} }, \
    { MODKEY|WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,SKEY,toggletag, {.ui = 1 << TAG} }
#define TAGKEYS(KEY,SKEY,TAG) \
    TAGKEYS1(KEY,SKEY,TAG), \
    TAGKEYS1(XKB_KEY_KP_0+TAG, XKB_KEY_KP_0+TAG, TAG)

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define RUN(...) { .v = (const char*[]){ __VA_ARGS__, NULL } }

/* commands */
static const Key keys[] = {
	/* Note that Shift changes certain key codes: c -> C, 2 -> at, etc. */
    /* spawns */
    /* modifier                  key                 function        argument */
    { MODKEY,                    XKB_KEY_m,          spawn,          RUN("bemenu-run") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_M,          spawn,          RUN("desktop-menu") },
    { MODKEY,                    XKB_KEY_a,          spawn,          RUN("desktop-hotkey", "auto-type-pw") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_A,          spawn,          RUN("desktop-hotkey", "auto-type-user") },
    { MODKEY,                    XKB_KEY_w,          spawn,          RUN("xdg-open", "https://") },
    { MODKEY,                    XKB_KEY_e,          spawn,          RUN("pcmanfm-qt") },
    { MODKEY,                    XKB_KEY_q,          spawn,          RUN("desktop-hotkey", "emoji-menu") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_p,          spawn,          RUN("power-menu") },
    { MODKEY,                    XKB_KEY_F5,         spawn,          RUN("desktop-hotkey", "light-down") },
    { MODKEY,                    XKB_KEY_F6,         spawn,          RUN("desktop-hotkey", "light-up") },
    { MODKEY,                    XKB_KEY_F9,         spawn,          RUN("desktop-hotkey", "volume-down") },
    { MODKEY,                    XKB_KEY_F10,        spawn,          RUN("desktop-hotkey", "volume-up") },
    { MODKEY,                    XKB_KEY_F11,        spawn,          RUN("pavucontrol") },
    { MODKEY,                    XKB_KEY_F12,        spawn,          RUN("desktop-hotkey", "toggle-speaker") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_F12,        spawn,          RUN("desktop-hotkey", "toggle-mic") },
    { 0,                         XKB_KEY_Print,      spawn,          RUN("spectacle") },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Return,     spawn,          RUN("foot") },
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_Return,     spawn,          RUN("foot tmux") },
    { MODKEY,                    XKB_KEY_x,          spawn,          RUN("foot tmux") },

    /* window management */
	/* modifier                  key                 function        argument */
	{ MODKEY,                    XKB_KEY_j,          focusstack,     {.i = +1} },
	{ MODKEY,                    XKB_KEY_k,          focusstack,     {.i = -1} },
    { MODKEY,                    XKB_KEY_n,          incnmaster,     {.i = +1} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_n,          incnmaster,     {.i = -1} },
	{ MODKEY,                    XKB_KEY_h,          setmfact,       {.f = -0.05} },
	{ MODKEY,                    XKB_KEY_l,          setmfact,       {.f = +0.05} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_h,          setmfact,       {.f = -0.01} },
    { MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_l,          setmfact,       {.f = +0.01} },
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_h,          setmfact,       {.f = 1+mfact} },
    { MODKEY|WLR_MODIFIER_CTRL,  XKB_KEY_l,          setmfact,       {.f = 1+mfact} },
	{ MODKEY,                    XKB_KEY_Return,     zoom,           {0} },
	{ MODKEY,                    XKB_KEY_Tab,        view,           {0} },
    { MODKEY,                    XKB_KEY_BackSpace,  killclient,     {0} },
    { WLR_MODIFIER_CTRL|WLR_MODIFIER_SHIFT,XKB_KEY_Q,killclient,     {0} },
    { MODKEY,                    XKB_KEY_u,          setlayout,      {.v = &layouts[0]} },
    { MODKEY,                    XKB_KEY_i,          setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                    XKB_KEY_space,      setlayout,      {0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_space,      togglefloating, {0} },
	{ MODKEY, 					 XKB_KEY_o,    	     togglefullscreen, {0} },
	{ MODKEY,                    XKB_KEY_0,          view,           {.ui = ~0} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_parenright, tag,            {.ui = ~0} },
	{ MODKEY,                    XKB_KEY_comma,      focusmon,       {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY,                    XKB_KEY_period,     focusmon,       {.i = WLR_DIRECTION_RIGHT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_less,       tagmon,         {.i = WLR_DIRECTION_LEFT} },
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_greater,    tagmon,         {.i = WLR_DIRECTION_RIGHT} },
	TAGKEYS(          XKB_KEY_1, XKB_KEY_exclam,                     0),
	TAGKEYS(          XKB_KEY_2, XKB_KEY_at,                         1),
	TAGKEYS(          XKB_KEY_3, XKB_KEY_numbersign,                 2),
	TAGKEYS(          XKB_KEY_4, XKB_KEY_dollar,                     3),
	TAGKEYS(          XKB_KEY_5, XKB_KEY_percent,                    4),
	TAGKEYS(          XKB_KEY_6, XKB_KEY_caret,                      5),
	TAGKEYS(          XKB_KEY_7, XKB_KEY_ampersand,                  6),
	TAGKEYS(          XKB_KEY_8, XKB_KEY_asterisk,                   7),
	TAGKEYS(          XKB_KEY_9, XKB_KEY_parenleft,                  8),
	{ MODKEY|WLR_MODIFIER_SHIFT, XKB_KEY_Q,          quit,           {0} },

	/* Ctrl-Alt-Backspace and Ctrl-Alt-Fx used to be handled by X server */
	{ WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_Terminate_Server, quit, {0} },
#define CHVT(n) { WLR_MODIFIER_CTRL|WLR_MODIFIER_ALT,XKB_KEY_XF86Switch_VT_##n, chvt, {.ui = (n)} }
	CHVT(1), CHVT(2), CHVT(3), CHVT(4), CHVT(5), CHVT(6),
	CHVT(7), CHVT(8), CHVT(9), CHVT(10), CHVT(11), CHVT(12),
};

static const Button buttons[] = {
	{ MODKEY, BTN_LEFT,   moveresize,     {.ui = CurMove} },
	{ MODKEY, BTN_MIDDLE, togglefloating, {0} },
	{ MODKEY, BTN_RIGHT,  moveresize,     {.ui = CurResize} },
};
