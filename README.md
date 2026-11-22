# Move Active Window to Monitor

A Windhawk mod I made because I run one normal monitor and one vertical one, and I got tired of dragging windows across by hand. Now it's a keyboard shortcut.

## What it does

* **Right Ctrl + Left or Right Arrow** sends the window you're working in to the monitor on that side.
* **Right Ctrl + Right Shift + Left or Right Arrow** sends every window on your current monitor over to the next one.
* **Right Ctrl + Down Arrow** minimizes the top window so the one under it shows. Press it again to minimize the next one.
* **Right Ctrl + Up Arrow** brings minimized windows back one per press, the most recent first, each on top of the last.
* **Double tap Right Shift** moves keyboard focus to the other monitor, so you don't have to click over. A short outline flashes around the monitor that got focus. It is white by default, and you can pick another color (red, orange, yellow, lime, green, cyan, blue, purple, pink or black) in the mod settings, along with how see-through it is and how thick (1 to 5 pixels is the sweet spot).

Maximized windows stay maximized on the new monitor. Everything else keeps its size, gets centered, and shrinks to fit if the new screen is smaller (which matters a lot when you hop onto a vertical monitor).

The window stays focused after it moves, so you can keep tapping the shortcut to bounce it back and forth.

## How it differs from similar mods

* **Move Window to Monitor** (TomberWolf) and **Move and Gather Windows** (fjdiazt) are already in the Windhawk catalog and cover moving a window or gathering windows with configurable hotkeys. This mod is not a replacement for them.
* This one is for people who want everything on Right Ctrl chords: move the active window, move every window on the current monitor, minimize and restore the top window one at a time, and jump keyboard focus to the other monitor (with a short outline flash so you can see where it went).
* Using Right Ctrl on its own is what needs the low level keyboard hook, which is why it is a separate mod and not a setting in theirs. If you only need to move a window, one of those two is the simpler pick.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. In Windhawk, open the menu and pick **Create a new mod**.
3. Delete the placeholder code and paste in `move-active-window-to-monitor.wh.cpp` from this repo.
4. Hit **Compile**, then enable the mod.

## Good to know

* Monitors are ordered left to right the way they are in Windows display settings. If nothing sits on the side you pressed, nothing happens.
* Windows blocks normal programs from controlling windows that run as administrator, so those won't move. Win + Shift + Arrow still works on them.
* To tell Right Ctrl apart from Left Ctrl, the mod uses a low level keyboard hook. It only reacts to the shortcuts above, but while Right Ctrl is held, the arrow keys don't reach other apps. The whole hook is one section of the code if you want to read it.
* When moving all windows, it skips minimized ones, windows on other virtual desktops, tool windows, the desktop and the taskbar.
* If a key press does nothing, turn on debug logging in the mod's Advanced tab and check the log. It prints what it did for each press.

## Credit

Started from the Move Window to Monitor mod by TomberWolf and rebuilt around Right Ctrl, the active window, and moving everything at once. Credits to [sultansaad-dev](https://github.com/sultansaad-dev) as well. Released under the MIT license.
