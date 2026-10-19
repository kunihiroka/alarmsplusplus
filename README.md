Alarms++
==============

This is the source repositor for the Pebble watchapp "Alarms++"

The app can be found in the store: https://apps.getpebble.com/applications/54551598997cdfddaa000043

## このフォークでの変更点 (v7.8)

[reini1305/alarmsplusplus](https://github.com/reini1305/alarmsplusplus) からのフォークです。

- **新規アラームのデフォルトをワンタイムに変更**
  - 新しく作るアラーム、および「Reset」したアラームは、曜日がすべてオフ(＝ワンタイム)の状態で始まります。元のアプリでは全曜日オン(毎日リピート)でした。
  - 未使用スロットの判定も新しいデフォルトに合わせています。
- **既存データの移行**
  - 元のアプリで保存された未使用スロット(0:00・無効・説明なし・全曜日オン)を、初回起動時に一度だけワンタイムに変換します。ユーザーが設定したアラームは変更しません。
- **Pebble Time 2 (emery) 対応**
  - emery 用バイナリがない `pebble-ui-dialog-window` パッケージを、必要な機能だけの自前実装 (`src/ui_dialog_window.c`) に置き換えました。
- **現行 SDK でのビルド修正**
  - `wscript` に `js_entry_file` を指定。
  - `src/localize.c` の常に真になる NULL チェック(`-Werror=address` でエラーになる)を削除。
- バージョンを 7.8 に変更(メイン画面の表示で判別可能)。

### ビルドとインストール

```sh
pebble build
pebble install --phone <スマホのIP>
```

スマホの Pebble アプリで Developer Connection をオンにしておく必要があります。`build/alarmsplusplus.pbw` をスマホで直接開いてインストールすることもできます。

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
