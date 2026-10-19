Alarms++
==============

This is the source repositor for the Pebble watchapp "Alarms++"

The app can be found in the store: https://apps.getpebble.com/applications/54551598997cdfddaa000043

## Changes in this fork (v7.8)

Forked from [reini1305/alarmsplusplus](https://github.com/reini1305/alarmsplusplus).

- **New alarms default to one-time**
  - Newly created alarms, and alarms cleared with "Reset", start with no weekdays selected (one-time). The original app selected every weekday (repeat daily).
  - Unused-slot detection follows the new default.
- **Migration of existing data**
  - On first launch, unused slots saved by the original app (0:00, disabled, no description, all weekdays) are converted to one-time once. Alarms you have configured are left untouched.
- **Pebble Time 2 (emery) support**
  - Replaced the `pebble-ui-dialog-window` package, which ships no emery binary, with a minimal local implementation (`src/ui_dialog_window.c`).
- **Build fixes for the current SDK**
  - Set `js_entry_file` in `wscript`.
  - Removed an always-true NULL check in `src/localize.c` that fails with `-Werror=address`.
- Version bumped to 7.8 (shown on the main screen).

### Build and install

```sh
pebble build
pebble install --phone <phone IP>
```

Enable Developer Connection in the Pebble app on your phone first. Alternatively, open `build/alarmsplusplus.pbw` on your phone to install it.

<a href='https://pledgie.com/campaigns/28156'><img alt='Click here to lend your support to: Christian Reinbachers Pebble Apps and make a donation at pledgie.com !' src='https://pledgie.com/campaigns/28156.png?skin_name=chrome' border='0' ></a>

#Screenshots
<img src="https://github.com/reini1305/alarmsplusplus/raw/master/store/aplite/pebble_screenshot_2015-08-15_12-10-23.png"></img>
<img src="https://assets.getpebble.com/api/file/mLDugb9JQjucO6KZHeNa/convert?cache=true&w=144&h=168&fit="></img>
<img src="https://github.com/reini1305/alarmsplusplus/raw/master/store/chalk/pebble_screenshot_2015-10-16_07-10-08.png"></img>
<img src="https://github.com/reini1305/alarmsplusplus/raw/master/store/basalt/pebble_screenshot_2015-08-15_12-47-39.png"></img>


#Features
- 16 alarms (32 on Pebble Time)
- each alarm can be customized to different weekdays
- flexible snooze interval
- optional long-press-to-dismiss-alarm
- optional increasing vibration strength (thanks to the great library of Jeff Blum: https://github.com/jeffbl/pebble)
- description per alarm, shown during alarm (thanks to tertiary text of Ricky Ayoub: https://github.com/vgmoose/tertiary_text)

#Credits
Credits go to Matthew Tole and his Multi-Timer app, which helped me a lot in structuring the code and mastering MenuLayers: https://github.com/smallstoneapps/multi-timer
