EWX 14 washing machine

```
10 - ???
   00 
      1B - wakeup (broadcasted at power on, sent to the inverter directly in some cases)
      17 - wakeup pong
   01 - wakeup pong ack? (sent directly from front panel to controller)
```

```
11 - sw provisioning
   00 - (sent by the front panel at power up)
      55 44 41 30 4D 32 31 31 43 - sw version "UDA0M211C"
                                 11 53 5F FD 03 00 00
      4D 30 4C 43 30 36 36 33 - inverter fw version "M0LC0663"
                              FF FF
   01 - (sent by the controller at power up)
      00 00
      34 7A 00 F5 00 50 00 08 00 20 00 55 00 00 - sent to inverter after config load
   03 - configuration load
      xx - data nr
         xx*20 data bytes
```

```
50 - program change (usually from panel to controller, but can be heard from controller)
   03 - ???
      00 - reset
      xx - water temperature
      1E - 30
      28 - 40
      3C - 60
         00 - reset
         xx - spin (50x value)
         10 - 800
         18 - 1200
         1C - 1400
            00 - not baby
            80 - baby
               00
               20 - time 1 ???
                  00
                  x1 - easy iron
                  x4 - stain
                  1x - extra rinse
                  2x - soft plus
                     x1 - time 5
                     x2 - time 4
                     x8 - time 3
                     1x - time 2
                     00 - time 1
                     41
                     8x - prewash
                        00
                        01
                        11
                           00
                           xx - delay (x30min)
                              00
                              02 - extra rinse
                                 00
                                    xx - program
                                       00
```

```
51 - change state
   00 
      41 - start diag mode (screen scrolling)
      4x - diag mode c0x
      45 - diag mode 5
      25 - diag mode 5 start btn
      60 - start program
         00 
            00 - start washing
               1B 03
      62 - pause program
      73 - show working time
      7D - power on/off
         02 17 - off
         01 17 - power on 1
         00 17 - power on 2
         01 16 - power off timeout
         04 16 - demo mode ?
         04 17 - demo mode ? off?
         06 17 - demo mode ? on?
```


```
52 - appliance state
   00
      01 - power on, not running
      02 - running
         00 - idle
         01 - pre-wash
         02 - wash
         03 - rinse
         04 - spin
            00
            01
            08
            80
               x2 - door open
               x1 - door lock requested
               1x - door locked
               00
               03
               11
               13
               15
               25
                  00 
                     00 - only in diag mode
                     40 
                     C0
                        2C 00
      03 - finished (after anti-crease)
      04 - pause
      06 - waiting for door lock to release
      08 - delayed start
      09 - error
         00 00 00 00
      0B - power off
         00 00 ...
```

```
54 - diag mode related?
   00 00 
         31
         33
         34 
            15 00 
                  xx - running program
                     00 00 00 00 00
```

```
55 - ???
   00
      B0
         1C
         9C
            14
               81
               83
                  00
                  80
                  D1
                     00 27 FF 28 0E 00 00
```


```
56 - time
   03
      00 - program time
         00 00 - display turn on, empty or 0 minutes
         00 0A - time 10 minutes
         FF FF - display turn off
      01 - delay start remaining time
         xx xx - value x 10 seconds
         02 45 - ca. 97 mins
      02 - total washed hours counter, sent sometimes or when requested
         xx xx - hours * 10
         01 F8 - 504 -> 50,4 Hr
               xx xx - previous field repeated
                     00 00 00 00
      03 - wash cycle count
         xx xx - wash cycle count
               xx xx - previous field repeated
                     00 00 00 00
         00 01 00 01 00 00 00 00
         00 02 00 02 00 00 00 00
         00 07 00 07 00 00 00 00
      04 
         00 00 46 00
         00 00 1E 00
      07
         00 76 - clothes+ off
         xx xx
      08 - ???
         00
         02
         03
         04
         05
         06
      
```

```
57 - alarm (+1)
   00
      xx - current alarm
         xx - last alarm (and current if active)
   00 00 00 00 00
   00 41 41 00 00 - before getting E40
   00 00 41 00 00 - cleared E40
```

```
5F - heartbeat
   03
```



## Inverter


```
10 00 1B
10 00 17
10 01
11 00 4D 30 4C 43 30 36 36 33 FF FF
11 03 00 00 7C 7D AB 03 E1 5C 40 0D C3 06 E2 06 66 03 13 03 B1 6F 46
11 03 01 5B 25 61 BF 02 40 31 28 01 FB 79 99 18 31 01 4B 6D 8C 5D 66
11 03 02 06 A4 FF FF FF FF 0A 3D 00 05 27 A1 3B 71 6E D9 01 DB 00 01
11 03 03 09 21 09 73 02 D5 08 AB 3F 02 FF FF FF FF FF FF FF FF FF FF
11 03 04 FF FF FF FF 00 5F 00 64 22 DB 7B F6 00 05 7F F0 00 03 29 F7
11 03 05 29 F7 01 2C 53 1E 00 6F 17 70 3B 71 00 64 01 90 FF FF FF FF
11 03 06 FF FF 01 00 9C C9
11 01 34 7A 00 F5 00 50 00 08 00 20 00 55 00 00
AD 00 04 B4 3C 23 1E 2C 54 60 02 E9
```

```
12 
   00 - from controller to inverter
      00 00
      01 AB
      01 E8
      02 25
      02 62
      02 DC
      -----
      BF 30
      C6 D0
      CB 94
      D0 58
      D7 7E
      DC 42
      E1 06
      EA 8E
      F1 B4
      F6 78
      F9 91
      FB 3C
      FC AA
      FD 24
      FD 92
      FD 9E
      FD DB
      FE 18
            00 55
            00 7A
            00 B7
            00 F4
            01 E8
            03 D0
            05 B8
            0E 4C
                  0C 9D
                  0E C0
                  0F C8
                  10 D9
                  12 F2
                  13 88
                  14 04
                  15 15
                  1B 69
                  1C 70
                  1D 82
                  1E 94
                        00
                        02
                        04
                        08
                        20
                           00
                           10
                           11

   03 - from inverter to controller
      xx xx - motor speed
            xx xx
                  xx - Drum temperature like ?
                     xx - controller temperature like
                        xx xx
                              00
                              01 
                                 00
                                    00
                                    20
                                       xx xx - Water level
                                             xx
                                                00 00
                                                01 AB
                                                01 E8
                                                02 25
                                                02 62
                                                02 DC
                                                BF 30
                                                C6 D0
                                                CB 94
                                                D0 58
                                                D7 7E
                                                DC 42
                                                E1 06
                                                EA 8E
                                                F1 B4
                                                F6 78
                                                F9 91
                                                FB 3C
                                                FC AA
                                                FD 24
                                                FD 92
                                                FD 9E
                                                FD DB
                                                FE 18
                                                      xx
                                                         xx xx - speed target
```

```
15
   00 02 62 - to inverter
            07
            08
            09
            0A
            0B
               xx
               04
               8C
               B3
               D9
               D1
               FC
               7B
               AB
                  00 1E 07 08 04 C4 05 
                                       14
                                       78
                                       DC
   01 00 - from inverter
```


```
16
   00  - to inverter
      03 B6
      FF FF
            06
            07
            08
            09
               04
               C3
               A5
               AE
               BC
                  00
   01 00 - from inverter
```

```
C9 - from inverter
   21 25 15 12
```

