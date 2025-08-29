/* Перечень регистров микросхемы MP42790 «MPS»*/

//============= Fuel Gauge Input
//16bit
#define VRDG_CELL1              0x0000  //Inputs cell 1’s voltage reading
#define VRDG_CELL2              0x0002  //Inputs cell 2’s voltage reading
#define VRDG_CELL3              0x0004  //Inputs cell 3’s voltage reading
#define VRDG_CELL4              0x0006  //Inputs cell 4’s voltage reading
#define VRDG_CELL5              0x0008  //Inputs cell 5’s voltage reading
#define VRDG_CELL6              0x000A  //Inputs cell 6’s voltage reading
#define VRDG_CELL7              0x000C  //Inputs cell 7’s voltage reading
#define VRDG_CELL8              0x000E  //Inputs cell 8’s voltage reading
#define VRDG_CELL9              0x0010  //Inputs cell 9’s voltage reading
#define VRDG_CELL10             0x0012  //Inputs cell 10’s voltage reading
#define VRDG_CELL11             0x0014  //Inputs cell 11’s voltage reading
#define VRDG_CELL12             0x0016  //Inputs cell 12’s voltage reading
#define VRDG_CELL13             0x0018  //Inputs cell 13’s voltage reading
#define VRDG_CELL14             0x001A  //Inputs cell 14’s voltage reading
#define VRDG_CELL15             0x001C  //Inputs cell 15’s voltage reading
#define VRDG_CELL16             0x001E  //Inputs cell 16’s voltage reading
#define VRDG_PACK               0x0020  //Inputs the pack’s voltage reading if VRDG_PACK_EN is enabled
#define TRDG_TS1                0x006A  //Inputs temperature sensor 1’s reading
#define TRDG_TS2                0x006C  //Inputs temperature sensor 2’s reading
#define TRDG_TS3                0x006E  //Inputs temperature sensor 3’s reading
#define TRDG_TS4                0x0070  //Inputs temperature sensor 4’s reading
#define TRDG_DIE                0x0072  //Inputs the die temperature reading
#define BAL_CELL                0x0074  //Indicates cell 1 - 16 balancing status (0 - 15 bits) boolean eatch bit
#define RST                     0x0076  //Отдельные биты см Datasheet
#define SHW                     0x0078  //Отдельные биты см Datasheet

//32bit
#define IRDG_CELL1              0x0022  //Inputs cell 1’s current reading if IRDG_CELLS_EN is enabled
#define IRDG_CELL2              0x0026
#define IRDG_CELL3              0x002A
#define IRDG_CELL4              0x002E
#define IRDG_CELL5              0x0032
#define IRDG_CELL6              0x0036
#define IRDG_CELL7              0x003A
#define IRDG_CELL8              0x003E
#define IRDG_CELL9              0x0042
#define IRDG_CELL10             0x0046
#define IRDG_CELL11             0x004A
#define IRDG_CELL12             0x004E
#define IRDG_CELL13             0x0052
#define IRDG_CELL14             0x0056
#define IRDG_CELL15             0x005A
#define IRDG_CELL16             0x005E  //Inputs cell 16’s current reading if IRDG_CELLS_EN is enabled
#define IRDG_PACK               0x0062  //Inputs the pack’s current reading if IRDG_PACK_EN is enabled
#define CCRDG                   0x0066  //Inputs the Coulomb count reading if CCRDG_EN is enabled

//============= Fuel Gauge Backup

//32bit
#define SOH_CELL1_BKUP          0x0200
#define SOH_CELL2_BKUP          0x0204
#define SOH_CELL3_BKUP          0x0208
#define SOH_CELL4_BKUP          0x020C
#define SOH_CELL5_BKUP          0x0210
#define SOH_CELL6_BKUP          0x0214
#define SOH_CELL7_BKUP          0x0218
#define SOH_CELL8_BKUP          0x021C
#define SOH_CELL9_BKUP          0x0220
#define SOH_CELL10_BKUP         0x0224
#define SOH_CELL11_BKUP         0x0228
#define SOH_CELL12_BKUP         0x022C
#define SOH_CELL13_BKUP         0x0230
#define SOH_CELL14_BKUP         0x0234
#define SOH_CELL15_BKUP         0x0238
#define SOH_CELL16_BKUP         0x023C

//16bit
#define IDIS_AVG_BKUP           0x023C


//============= Fuel Gauge Output
//8bit
#define EMTY_SOC_CELL1          0x0564 //Returns cell 1’s empty SOC in %
#define EMTY_SOC_CELL2          0x0565
#define EMTY_SOC_CELL3          0x0566
#define EMTY_SOC_CELL4          0x0567
#define EMTY_SOC_CELL5          0x0568
#define EMTY_SOC_CELL6          0x0569
#define EMTY_SOC_CELL7          0x056A
#define EMTY_SOC_CELL8          0x056B
#define EMTY_SOC_CELL9          0x056C
#define EMTY_SOC_CELL10         0x056D
#define EMTY_SOC_CELL11         0x056E
#define EMTY_SOC_CELL12         0x056F
#define EMTY_SOC_CELL13         0x0570
#define EMTY_SOC_CELL14         0x0571
#define EMTY_SOC_CELL15         0x0572
#define EMTY_SOC_CELL16         0x0573 //Returns cell 16’s empty SOC in %
#define EMTY_ID                 0x0574 //Returns 1 to 16 the cell ID for the cell that is empty limiting the pack
#define EMTY_LIM                0x0577 //Outputs the pack’s empty limiting factor
#define FULL_SOC_CELL1          0x057C //Returns cell’s 1 full SOC in %
#define FULL_SOC_CELL2          0x057D
#define FULL_SOC_CELL3          0x057E
#define FULL_SOC_CELL4          0x057F
#define FULL_SOC_CELL5          0x0580
#define FULL_SOC_CELL6          0x0581
#define FULL_SOC_CELL7          0x0582
#define FULL_SOC_CELL8          0x0583
#define FULL_SOC_CELL9          0x0584
#define FULL_SOC_CELL10         0x0585
#define FULL_SOC_CELL11         0x0586
#define FULL_SOC_CELL12         0x0587
#define FULL_SOC_CELL13         0x0588
#define FULL_SOC_CELL14         0x0589
#define FULL_SOC_CELL15         0x058A
#define FULL_SOC_CELL16         0x058B //Returns cell’s 16 full SOC in %








//16bit
#define EMTY_RTIME              0x0575 //Returns the  seconds remaining time for the pack to become empty











