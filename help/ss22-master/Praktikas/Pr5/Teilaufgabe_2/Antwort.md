# Wieso muss das Feld die Speicherklasse static erhalten?

Da die Variable nur im Funktionskontext vorhanden ist und sobald diese
an die aufrufende Funktion zurueckkehrt, wird das Feld ungueltig.

Es gibt prinzipiell drei Wege dieses Problem zu "reparieren":
1. Eine static Variable nutzen, um die Variable auch nach dem Verlassen
   der Funktion zu "behalten".

2. Mit dynamischer Speicherreservierung arbeiten, um das Problem welches
   in der zweiten Frage noch mal aufgegriffen wird zu umgehen.
   Nachteil: Nutzer muss ich um das "Loeschen" des Speichers selbst
   kuemmern.

3. Puffer nicht selbst in der Fn. deklarieren und definieren, sondern via
   Funktionsparameter uebergeben, wie es praktisch bei fast jeder System-
   bilbiotheksfunkion der Fall ist.
   Das ist der beste Fall, da somit die wenigsten Nachteile auftreten.

# Was muessen Sie beachten, wenn die Fn. mehrmals nacheinander in einem Prog. aufgerufen wird?

Beim mehrmaligen Aufrufen der Fn. veraendert sich der Wert des Feldes
nicht. Sprich sie ist dann nicht mehr NULL, sondern hat den davorigen Wert.
Kann man zwar loesen, muss man bloss aufpassen.

Ich habe zwei Moeglichkeiten verwendet, eine die wie in der Aufgabe es
gefordert ist mit einer static Variable und eine wo dynamische Speicher-
reservierung gearbeitet wird.

Am besten waere allerdings die 3. Loesung, da sie verglichen zu den
anderen beiden Varianten keine Gefahren mit sich bringt. Da diese allerdings
nicht nur ein klein wenig die Aufgabe veraendern wuerde, sondern die
komplette Signatur der Funktion aendert, habe ich es dabei belassen.
