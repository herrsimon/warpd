warpd(1)

# DESCRIPTION

A modal keyboard driven pointer manipulation program.

# SYNOPSIS

warpd [options]

# OPTIONS

	*-f*, *--foreground*: Run warpd in the foreground. Mainly useful for debugging.

	*-l*, *--list-keys*: Print a list of valid keys which can be used as config values.
	*--list-options*: Print all configurable options.

	*-v*, *--version*: Print the current version.

	*-c*, *--config* <config file>: Use the provided config file.

	*--hint*: Run warpd in oneshot (daemonless) hint mode.

	*--grid*: Run warpd in oneshot grid mode.

	*--normal*: Run warpd in oneshot normal mode.

# DESCRIPTION

warpd has three main modes which can be used to manipulate the pointer. The
primary mode is called 'normal mode' (A-M-c) and facilitates local pointer
movement using vi-like bindings (_h_ _j_ _k_ _l_). The other two modes, *hint*
and *grid* mode are used to effect larger movements across the screen and are
expected to be used in combination with normal mode to achieve the desired end.

For example, the user might activate warpd in hint mode (_A-M-x_) to pinpoint
the start of a text region before starting a drag operation (_v_) and
ultimately using normal mode to complete the selection. If the selection is a
large body of text, it may be desirable to activate grid (_g_) or hint (_x_)
mode for a second time to warp the pointer to the desired region's terminal
point.  

A description of each mode follows (see also _USAGE_NOTES_):

## Normal Mode (A-M-c)

This is the default mode (and the endpoint of both grid and normal mode) which
is designed for short distance pointer manipulation. It is particularly useful
for manipulating popup menus and selecting text (see _Dragging_). The default
behaviour is vi-like. Pressing the mapped directional keys (default hjkl) moves
the cursor in a continuous fashion, but the pointer can also be warped to the edges
of the screen using the home (_H_), middle (_M_), and last (_L_) mappings.
Finally, a numeric multiplier can be supplied to the
directional keys as an input prefix in order to move the cursor by a
proportional increment in the given direction (e.g 10j moves 10 units down). 

## Hint Mode (A-M-x or simply 'x' within normal mode)

This mode populates the screen with a list of labels and allows the
user to immediately warp the pointer to a given location by pressing the
corresponding key sequence. It is similar to functionality provided by browser
plugins like Vimperator but works outside of the browser and indiscriminately
covers the entire screen. Once a target has been selected 'normal mode' is
entered for further manipulation.

*Note:* While it may at first be tempting to saturate the screen with hints,
the user is cautioned against this. A balance must be struck between hint size,
the number of hints, and the size of the screen. Enough space must be left to
provide contextual awareness, while enough hints must be present to facilitate
targetting UI elements without the need for too much adjustment. Once this
equilibrium has been achieved, using hint mode become second nature and is (in
the author's opinion) superior to grid mode for quickly pinpointing elements.

## Grid Mode ('A-M-g' or simply 'g' within normal mode)

By default grid mode divides the screen into a 2x2 grid. Each time a key
is pressed the grid shrinks to cover the targeted quadrant. The cursor is placed
in the middle of the grid.

covers the desired target a mouse button (e.g 'm') can be pressed.


E.G

```
         +--------+--------+            +--------+--------+
         |        |        |            |  u |  i |       |
         |   u    |   i    |            |----m----+       |
 M-x     |        |        |     u      |  j |  k |       |
----->   +--------m--------+   ----->   +---------+       |
         |        |        |            |                 |
         |   j    |   k    |            |                 |
         |        |        |            |                 |
         +--------+--------+            +--------+--------+
```

## Screen Selection Mode ('A-M-s' or simply 's' within normal mode)

This mode is intended for multi-screen setups and provides the user with a
dedicated set of hints for switching monitors and dropping them into normal
mode.

## Dragging

Pressing _v_ whilst in normal mode toggles a drag operation. The cursor can
then be warped around the screen as normal in order to select text or move
objects until the drag key is hit again or a mouse button is pressed.
Additionally, the *copy_and_exit* key (_c_) may be used to copy the selected
text to the system clipboard and terminate the current session.

## Wayland

Wayland's architecture does not allow clients to globally bind hotkeys. In
order to run warpd, one of the oneshot flags must be used. These can be bound
to the corresponding hotkeys in your compositor.

E.G

On sway:

```
bindsym Mod4+Mod1+x exec warpd --hint
bindsym Mod4+Mod1+c exec warpd --normal
bindsym Mod4+Mod1+g exec warpd --grid
```

Non-wayland users should favour the daemon, since it also caches some of the
draw operations to improve performance.

# CONFIG OPTIONS

The program can be modified by placing configuration options in 
*~/.config/warpd/config*, a complete list of which can be obtained
with _--list-options_.

Each option must be specified on its own line and have the format:

<option>: <value>

Options which accept multiple keys (e.g _grid_keys_) expect each key to
be separated by a space. Options which accept one or more keys
may be specified mulitple times, in which case all supplied mappings
are interchangeable.

# USAGE NOTES

The key to using warpd effectively is to learn when to exit normal mode. Much
of one's time at a computer is spent moving the mouse between windows,
interacting with UI elements, and reading text. What one might call 'browse
mode'. It is in this mode of operation that it makes sense to keep warpd
active.

Developing facility with the scroll and oneshot mouse buttons is key to
achieving this. For example, if you happen to have two documents open and wish
to switch between them, you can simply type _x fx_ (where _fx_ is a hint) if
normal mode is already active. Scrolling can subsequently be achieved using _e_ and
_r_. Once you finally wish to type something, you can do _x fx n_ to focus on
the UI element, click, and exit.

Conversely, warpd can complement an input heavy workflow with its oneshot
functionality and dedicated activation keys (E.G _n_, _A-M-l_, _A-M-x_, etc).  

It is important to note that warpd is not intended to replace mouse heavy
workflows, and will likely always be inferior for rapid precise local
movements. When confronted with an IDE, or some other pointer driven
abomination, the author still sometimes reaches for his mouse.

## On Dragging

Activating discrete mode and pressing v can provide a familiar environment to a
_vi_ user but it is important to remember that cursor manipulation is
application agnostic and consequently ignorant of the text on the screen. All
movement is necessarily pixel based, consequently, drag + hint
mode can be a superior method for surgically selecting text (though it may at
first be less intuitive).

# FILES

*$XDG_CONFIG_HOME/warpd/config*++
*~/.config/warpd/config*
	The path of the configuration file (searched in order).

# BUGS/LIMITATIONS

warpd uses various platform specific hacks to bypass limitations
of the display server. All implementations were written by the
same author, who presently uses X.

Consequently testing on non-X platforms has been minimal.

YMMV

Bugs can be reported here:

https://github.com/rvaiya/warpd/issues/

A list of known limitations follow:

- Multiscreen support currently does not support hotplugging. This means that
  you must restart warpd after making any changes to your screen configuration.

- For implementation reasons, the cursor position is not horizontally centered,
  but to the right of the actual pointer. This generally isn't an issue,
  but may become more noticeable as you increase _cursor_size_.

## X

- Unplugging the keyboard while warpd is one of its active modes will cause
  pandemonium.  If you do this (don't :P), you may need to remotely ssh into
  the machine or switch to a VT to kill the process.

- warpd uses Xinput for input processing to bypass certain limitation of the X
  input system. A byproduct of this is that certain remapping tools will not
  work (e.g xcape). If you are in the habit of making unorthodox changes to
  your keymap (like remapping capslock to control/escape) you may want to try
  an evdev based remapper like keyd (https://github.com/rvaiya/keyd).

- Programs which use Xinput to directly manipulate input devices may misbehave.
  See [Issue #3](https://github.com/rvaiya/warpd/issues/3#issuecomment-628936249) for details.

## MacOS

- Cursor hiding relies on a hack that some programs ignore (e.g iTerm).
- Some programs (e.g iTerm) have a 'secure input mode' (which can usually be
disabled) that causes interference.

## Wayland

- Cursor hiding doesn't work.
- Running as a daemon doesn't work (can't listen for hotkeys).
- UI elements (e.g input fields) which require focus can't be selected.

# AUTHORS

Written and maintained by Raheman Vaiya (2019-).
See https://github.com/rvaiya/warpd for more information.
