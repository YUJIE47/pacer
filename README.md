# pacer
pacer是一個穿戴型配速系統，利用藍芽連接手機與esp32來設定初始值，跑步時可不用攜帶手機，單由esp32來計算合適的配速，並且利用震動來提醒跑者當前速度需要調整。

---

### Required embedded devices
1. 開發版 Esp32-S3
2. 九軸感測器 MPU9255
3. 震動馬達 Grove – Vibration Motor
4. 觸控螢幕 8inch SPI Module ILI9341

### Connect all devices
依照下方電路圖接上所有設備
<img width=800 src="https://github.com/hsuantung/pacer/blob/main/pacer_circuit_diagram.png"/>

---

### Get started
參考下方的說明
1. 開server端，pacer.ino
2. 開client端，pacer_client.apk

### `pacer.ino`
裡面是esp32的程式，esp32是server
1. 燒錄進esp32，打開序列埠
2. 當手機端選擇完MyESP32-*，序列埠會印出client connected
3. 當手機端按下send按鈕，序列埠會收到初始值並印出Distance和Time

### `pacer_client.apk`
裡面是手機app程式，先安裝在手機
(目前適用Android手機)
1. 選擇要連接的server(基本上找MyESP32-*)
2. 填入跑步總距離跟總時長
3. 按下send按鈕，送出Distance和Time給esp32

---
### Go running
當設備偵測到開始跑步的時候，螢幕上就會顯示所有資訊，否則畫面為空
