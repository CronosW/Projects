Nume: Lisca Radu
Grupa: 341C2
Tema1 EGC


Pentru aceasta tema am folosit scheletul laboratorului 3 din cadrul cursului de Elemente de Grafica pe Calculator.
Pentru inceput am desenat pasarea din 4 componente:
	-un dreptungi
	-un cerc
	-doua triunghiuri

Pentru scena am folosit 4 tuburi fiecare avand 2 componente:
	-componenta de sus
	-componenta de jos

Aceste tuburi sunt formate din doua dreptunghiuri puse initial in scena la o distanta egala.
Pe masura ce jucatorul avanseaza acestea incep sa se fie desenate in scena la o distanta random dintr-un interval.
Tuburile se misca spre stanga cu o viteza initiala si odata ce ajung in capatul din stanga al scenei acestea sunt desenate 
in afara scenei mult in dreapta.
Elementele pasarii se deplaseaza constant in jos pe axa OY si inclinatia acesteia este orientata in jos cu ajutorul rotatiei.
Pe masura ce jucatorul avanseaza atat viteza de deplasare a pasarii cat si viteza de deplasare a tuburilor creste pana la un prag limita.

Am folosit un fisier in care am retinut Best_Score de fiecare data cand jucatorul pierde.
Pentru coliziuni am verificat fiecare componenta a pasarii sa nu se afle la suprafata sau in interiorul celor doua componente ale tubului.
Daca jucatorul pierde se va afisa in consola Scorul acestuia precum si Best_Score. Si se deseneaza pe ecran din patrate si cercuri
mesajul Game Over.
