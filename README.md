# Multi-Monitor Window Controls

A Windhawk mod I made because I run one normal monitor and one vertical one, and I got tired of reaching for the mouse every time I wanted to juggle windows between them.

## What it does

These are the defaults. Every shortcut can be changed or turned off in the mod settings.

| Shortcut | What it does |
|---|---|
| Right Ctrl + Down | Minimizes the top window so the one under it shows. Press again for the next one. |
| Right Ctrl + Up | Brings back the last window you minimized this way, on top. One per press. |
| Double tap Right Shift | Moves keyboard focus to the next monitor, so you don't have to click over. |
| Right Ctrl + Right Shift + Up / Down | Moves focus to the next / previous monitor. |
| Right Ctrl + Left / Right | Sends the window you're working in to the monitor on that side. |
| Right Ctrl + Right Shift + Left / Right | Sends every window on your current monitor to the one on that side. |

When focus switches, a short outline flashes around the monitor that got it so you can see where you landed. You can change its color, opacity and width, or turn it off.

Maximized windows stay maximized on the new monitor. A single moved window keeps its size, gets centered, and shrinks to fit if the new screen is smaller (which matters a lot when you hop onto a vertical monitor). When you move everything at once, each window keeps its spot relative to the screen instead of piling up in the middle.

## Settings

* **Each shortcut**: pick the key (a letter, digit, arrow, F1 to F24 and so on) and up to two modifiers (Ctrl, Shift or Alt, left, right or either side). Leave the key empty to turn a shortcut off. Handy if your laptop has no Right Ctrl.
* **Double tap key**: Right or Left Shift, Ctrl or Alt, or off. Turn it off if an app you use has its own double tap, like double Shift in JetBrains IDEs.
* **Focus outline**: on or off, color, opacity and width. The width scales up on high DPI screens.

## How it differs from similar mods

[Move Window to Monitor](https://windhawk.net/mods/move-window-to-monitor), [Move and Gather Windows](https://windhawk.net/mods/gather-windows-to-monitor) and [Snap Commander](https://windhawk.net/mods/snap-commander) can already move windows between monitors. If that's all you need, use one of those. This mod is built around the parts they don't have: minimizing and restoring windows one at a time, and jumping keyboard focus between monitors (with a double tap and an outline flash). Moving windows is included so all your multi-monitor shortcuts can live on one modifier key, like Right Ctrl on its own.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. In Windhawk, open the menu and pick **Create a new mod**.
3. Delete the placeholder code and paste in `multi-monitor-window-controls.wh.cpp` from this repo.
4. Hit **Compile**, then enable the mod.

## Good to know

* A key press is only blocked when it matches a shortcut and that shortcut actually has something to do. So Right Ctrl + Left still does word navigation in a text box when there's no monitor on the left.
* The mod uses a low level keyboard hook, because normal hotkeys can't tell Right Ctrl from Left Ctrl or catch a double tap. Nothing is recorded or sent anywhere.
* Windows blocks normal programs from controlling windows that run as administrator, like Task Manager, so shortcuts do nothing on those.
* If a key press does nothing, turn on debug logging in the mod's Advanced tab and check the log.

## Credit

The move logic started from the Move Window to Monitor mod by TomberWolf. Credits to [sultansaad-dev](https://github.com/sultansaad-dev) as well. Released under the MIT license.
