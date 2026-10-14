# LAB 4

ex01 Scanning Wi-Fi networks.

1.1 exercico 

**arduino-cli compile --fqbn esp32:esp32:esp32s3 --board-options CDCOnBoot=cdc .**

**arduino-cli upload -p /dev/ttyACM0 --fqbn esp32:esp32:esp32s3 --board-options CDCOnBoot=cdc .**

**INUX ➜ arduino-cli monitor -p /dev/ttyACM0 -c baudrate=9600**


Monitor port settings:
  baudrate=9600
  bits=8
  dtr=on
  parity=none
  rts=on
  stop_bits=1

Connecting to /dev/ttyACM0. Press CTRL-C to exit.
Setup done
scan start
scan done
22 networks found
1: AndroidAP6193 (-47)*
2: comcs2627m1ag67 (-50)*
3: eduroam (-51)*
4: comcs2627m1ag9944 (-52)*
5: ISEPWLAN (-52)
6: labs (-52)*
7: Eduroam-guest (-53)
8: Layla (-55)*
9: comcs2627m1ag004 (-56
10: comcs2627m1ag03 (-57)*
11: comcs2627m1ag13 (-61)*
12: REDMI Note 15 Pro+ 5G (-63)*
13: Schweizer (-65)*
14: ETs (-65)*
15: naoseiqualeomeuiddegrupo (-69)*
16: Homepot (-71)*
17: comcs2526m1ag99 (-75)*
18: ISEPWLAN (-75)
19: Eduroam-guest (-78)
20: TP-Link_97A6 (-80)*
21: ESP_FB3131 (-93)*
22: ISEPWLAN (-93)

scan start
scan done
22 networks found

---



---





# ex04 multi-useconcurrent handling

---

# Blueotooth 

bluetoothctl --timeout 15 scan on | grep -i "7c:2c:67:8b:d7:e9"
