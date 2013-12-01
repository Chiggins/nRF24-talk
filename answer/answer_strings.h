prog_char FreeMemory[] PROGMEM = "freeMemory()=";
prog_char TrigRandMass[] PROGMEM = "Triggered random mass send.";
prog_char ChangeAnswer[] PROGMEM = "Changed default answer to ";
prog_char TrigMass[] PROGMEM = "Triggered unanimous mass send.";
prog_char TrigSingle[] PROGMEM = "Triggered single send.";
prog_char ClearedStats[] PROGMEM = "Cleared Statistics.";
prog_char FinRandMass[] PROGMEM = "Finished random mass send.";
prog_char FinMass[] PROGMEM = "Finished unanimous mass send.";
prog_char FinSingle[] PROGMEM = "Finsihed sending single answer";
prog_char ChannelSet[] PROGMEM = "Channel set to ";
prog_char DefaultMode[] PROGMEM = "Entering Default Mode";
prog_char AutoAnswer[] PROGMEM = "Entering Auto Answer Mode";
prog_char ChangedByAA[] PROGMEM = "Auto-Answer sent new answer: ";
prog_char BeforeCipher[] PROGMEM = "Before cipher:";
prog_char AfterCipher[] PROGMEM = "After cipher:";
prog_char AfterDecode[] PROGMEM = "After decoding:";
prog_char NewLine[] PROGMEM = "";

prog_char Registers[] PROGMEM = "<registers>";
prog_char Colen[] PROGMEM = ": ";
prog_char RegistersN[] PROGMEM = "</registers>";

prog_char Macs[] PROGMEM = "<macs>";
prog_char MacsN[] PROGMEM = "</macs>";
prog_char MacsFormat[] PROGMEM = "%02X ";
prog_char Stats[] PROGMEM = "<stats>";
prog_char StatFormat[] PROGMEM = "%c: %3hu - ";
prog_char Percent[] PROGMEM = "%";
prog_char Total[] PROGMEM = "Total: ";
prog_char PopularAnswer[] PROGMEM = "Popular answer: ";
prog_char StatsN[] PROGMEM = "</stats>";
prog_char EnterReceiveMode[] PROGMEM = "Entering receive as clicker master mode...";

prog_char ConstantCarrierMode[] PROGMEM = "Entering constant carrier mode...";
prog_char TransmitCarrier[] PROGMEM = "Transmitting Carrier.";
prog_char EnterTransmitMode[] PROGMEM = "Entering send as clicker mode...";

prog_char Help[][70] PROGMEM = {  "------------------------------------------------",
                                  "  nRF24L01 Fake Clicker v1                      ",
                                  "        -By Taylor Killian                      ",
                                  "            http://www.taylorkillian.com        ",
                                  "                                                ",
                                  "  h - This help screen                          ",
                                  "  r - Read nRF24L01 registers                   ",
                                  "  g - Send out random answers for all clickers  ",
                                  "  m - Send out the same answer for all clickers ",
                                  "  s - Send out an answer for one clicker        ",
                                  "  c? - Change answer to send to ?               ",
                                  "  t - Show statistics from other clickers       ",
                                  "  n - Next question, restart statistics         ",
                                  "  ; - Seperates commands                        ",
                                  "  fNN. - Channel is set to NN                   ",
                                  "  a - Auto-Answer Questions                     ",
                                  "  d - Do not Auto-Answer Questions              ",
                                  "  p - Display the recorded MACs                 ",
                                  "  j - Send out a constant carrier               ",
                                  "                                                ",
                                  "  Ex: c4m;c1s                                   ",
                                  "        -All clickers send out '4' as answer    ",
                                  "        -Then single cicker sends out '1'       ",
                                  "------------------------------------------------" };
