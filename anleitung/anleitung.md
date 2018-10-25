#fizzi

##Board
Das fizzi board lässt sich in 5 Baugruppen unterteilen:

**1. Microcontroller**  
Der Microcontroller, ein Attiny 861 ist das Herzstück des fizzi Boards.
Alle Anschlüsse können über die Pinleiste unterhalb des Microcontrollers erreicht werden.
Über den ICSP-Anschluss kann der Attiny programmiert werden.  
  
![ov1](bilder/overview-01.png)

Anschlüssse übersicht 

**2. Stromversorgung**  
Der Schaltkreis auf dem fizzi Board wird mit einer Spannung von 5 Volt betrieben. Damit auch Batterien oder Akkus verwendet werden können, verfügt das Board über einen stepup Converter. Dadurch lässt sich es sich mit einer Spannung von 2,5 bis 4,5 Volt betreiben. Am oberen Rand befindet sich der Spannungseingang, direkt rechts daneben Anschlüsse für einen Ein-/Ausschalter.
Des Weiteren gibt es zwei Anschlüsse, an denen jeweils 5V und Ground zur verfügung stehen.  
  
![ov2](bilder/overview-02.png)
	
**3. Protoarea**  
Die Protoarea ist ein Lochrasterfeld im standrard Rastermaß (2,54mm) mit einer Größe von 16x25 Lötpunkten. Darauf können Bauteile platziert werden, die für 
die Integration verschiedener Interface-Elemente benötigt werden. An den Seiten der Protoarea befinden sich Powerrails zur einfachen Verteilung von +5 Volt und Ground. Diese Powerrails müssen mit den Stromanschlüssen auf dem Hauptteil der Platine verbunden werden. Falls die Protoarea nicht benötigt wird, kann sie einfach abgebrochen werden.  
  
   
![ov3](bilder/overview-03.png)

**4. Audio Output**  
Der 3,5mm Klinke Audioausgang befindet sich in der linken oberen Ecke des Boards. Außerdem ist links an der Seite noch ein Anschluss für einen 1 bis 2 Watt Lautsprecher. Um die Lautstärke zu regulieren kann an der vorgesehen stelle ein kleiner Trimmer eingesetzt werden. Das ist praktisch wenn man das fizzi Board nur zum prototypen verwendet, ansonsten empfielt es sich ein mit kabeln verbundenes Poti zu verwenden um sich später den Einbau in ein Gehäuse zu erleichtern. Die mit "LPPOT" beschrifteten Pins können einfach mit einem Jumper verbunden werden,oder man verbindet die beiden Pins mit dem Schleifer und einem der äußeren Kontakte eines 10k Potentiometers. So erhält man einen regulierbaren Lowpass Filter.  
  
![ov4](bilder/overview-04.png)

lautsprecher widerstand

**5. Sync Input**    
Der Eingang für ein Taktsignal befindet sich direkt neben dem Audioausgang.
Um die Elektronik auf dem Board zu schützen ist der Eingang durch einen Optokoppler von der restlichen Schaltung getrennt. Direkt neben dem Eingang befinden sich Anschlüsse für eine Kipp- oder Schiebeschalter. Mittels diesem Schalter kann der sync mode aktiviert oder deaktiviert werden. Das Umschalten wird allerdings nur registriert, wenn es vor dem Einschalten des Boards passiert. Ein Umschalten während das Board eingeschaltet ist hat keinen effekt. Die Verbindung zwischen dem Microcontroller und dem Eingang lässt sich am "SJMP" jumper auftrennen. So kann der Pin am Microcontroller für andere zwecke verwendet werden wenn der sync mode nicht benötigt wird.

![ov5](bilder/overview-05.png)

##Programmierung
Das fizzi Board kann mit der Arduino IDE programmiert werden. Damit das klappt muss zuerst der ATtiny Core von Spence Konde installiert werden. Gehe dazu in der Arduino IDE auf **Datei -> Einstellungen** und füge diese URL __http://drazzy.com/package_drazzy.com_index.json__ zu den "Zusätzlichen-Boardverwalter-URLs" hinzu. Nun kannst du unter **Werkzeuge->Board->Boardverwalter** den Core finden und installieren.
Zum Programmieren des Boards benötigt man einen ISP-Programmer, man kann dafür aber auch einfach einen Arduino Uno als Programmer verwenden. Übertrage dafür den **ArduinoISP** Sketch der unter **Datei->Beispiele->11.ArduinoISP** zu finden ist auf den Uno. Anschließende muss noch ein 10µF Kondensator zwischen **RESET** und **GND** platziert werden, so dass der negative Pol des Kondensators mit **GND** verbunedn ist. Das folgende Diagramm zeigt, wie der Arduino mit dem ICSP-Anschluss auf dem fizzi Board verbunden werden muss.  

![icsp](bilder/icsp-header.png)
  
Stelle nun unter **Werkzeuge** folgendes ein:  
• Board: ATtin 261/461/861  
• Clock: 16Mhz(external)  
• Chip: ATtiny 861  
• B.O.D. Level: disabled  
• Save EEPROM: EEPROM retained  
• Timer 1 Clock: 64 Mhz  
• LTO: disabled  
• Programmer: Arduino **as** ISP  
  
Als nächstes muss der Bootloader auf den ATtiny gebrannt werden indem man **Werkzeuge-> Bootloader brennen** auswählt. Wenn das erledigt ist kann man den fizzi_start Sketch der unter **Datei->Beispiele->fizzi** zu finden ist auf das Board übertragen, am jetzt sollte bereits der erste Ton zu hören sein.
Struktur bla bla
