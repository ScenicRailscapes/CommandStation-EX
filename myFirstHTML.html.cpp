#include <Arduino.h>
String myFirstHTML_html=R"???(
Set delay between signal red and turnout throw 
<cvinput cv=43 min="0" max="1000" />mS
<br/>
Set delay between turnout throw and signal green
<cvinput cv=44 min="0" max="1000" />mS
)???";


// CONFIGURE_DIALOG("My simple demo",myFirstHTML) dit in myAutomation.h plaatsen , dit zet een config dialoog onderaan de webpagina van de DCC-EX   