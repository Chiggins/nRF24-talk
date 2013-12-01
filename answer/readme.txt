"------------------------------------------------"
"  nRF24L01 Fake Clicker v1                      "
"        -By Taylor Killian                      "
"            http://www.taylorkillian.com        "
"                                                "
"  h - This help screen                          "
"  r - Read nRF24L01 registers                   "
"  g - Send out random answers for all clickers  "
"  m - Send out the same answer for all clickers "
"  s - Send out an answer for one clicker        "
"  c? - Change answer to send to ?               "
"  t - Show statistics from other clickers       "
"  n - Next question, restart statistics         "
"  ; - Seperates commands                        "
"  fNN. - Channel is set to NN                   "
"  a - Auto-Answer Questions                     "
"  d - Do not Auto-Answer Questions              "
"  p - Display the recorded MACs                 "
"  j - Send out a constant carrier               "
"                                                "
"  Ex: c4m;c1s                                   "
"        -All clickers send out '4' as answer    "
"        -Then single cicker sends out '1'       "
"------------------------------------------------"

Be sure to change myMAC and oppositeMyMac to your clickers MAC address before using.
myMac should appear how it it written on the back of the clicker and oppositeMyMac should
have the bytes swapped.

EX:

Written:
    Device ID: ABCDEF

Code:
    byte myMAC[MAC_SIZE] = { 0xAB, 0xCD, 0xEF };
    byte oppositeMyMAC[MAC_SIZE] = { 0xEF, 0xCD, 0xAB };
 