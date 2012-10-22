Projekteinstellungen für Nibo2 
	unter Ubuntu 10.04 LTS 32bit innerhalb VirtualBox
	UCOM-IR 2 gemountet an /dev/ttyS0
-------------------------------------------------

Zum schnellen Wiederverwenden der Projekteinstellungen, 
einfach dieses Projekt kopieren und einfügen, statt ein neues zu erstellen

! Hinweis für Subversion-Nutzer, die die Projekte einzeln auschecken: 
Wenn man ein Projekt kopiert, werden auch die svn-Daten kopiert, wodurch das
neue Projekt in den gleichen Repository-Pfad kopiert wird, wie dass, von dem kopiert wurde. Daher sollte
man nach dem Kopieren folgendes machen:
Rechtklick auf's Projekt -> Team -> Disconnect
Im folgenden Dialog folgende Option wählen 'Also delete the SVN meta information from the file system'
Anschließend via Team -> Share Project das neue Project auschecken
	
-------------------------------------------------

AVR -> AVR Dude -> Programmer Configuration -> New
	im neuen Dialog
		Programmer Hardware (-c) -> 'Atmel STK500 Version 2.x firmware'
		Override Port (-P) -> '/dev/ttyS0'
		Configuration Name -> Namen eingeben, zB 'Atmel STK 500 ttyS0'
		'OK'
		
C/C++ Build -> Settings
	im Tab Tool Settings
		Additional Tools in Toolchain -> Haken bei 'Generate HEX file for Flash memory'
		AVR Compiler -> Directories -> Pfad zum NiboLib\include Verzeichnis hinzufügen
		AVR Compiler -> Optimization -> Optimization Level -> Size Optimizations (-Os)
		AVR Compiler -> Miscellaneous -> Other flags -> -D_NIBO_2_
		AVR C Linker -> General -> Other Arguments -> -u,vfprintf
		AVR C Linker -> Libraries -> Libraries Path (-L) -> Pfad zum NiboLib\lib Verzeichnis hinzufügen
								  -> Libraries (-l) -> nibo2
								  					-> m
								  					-> printf_flt
											ggf.:   -> nds3
													-> xbee-1