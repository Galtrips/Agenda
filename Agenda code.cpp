#include <iostream>
#include <fstream>
#include <ctime>
#include <cstring>
#include "TP4.h"

using namespace std;

void initHoraire(Horaire& horaire, int h, int m) {

    horaire.h = h;
    horaire.m = m;

}

int horComp(Horaire& h1, Horaire& h2) {
    
    if (h1.h == h2.h && h1.m == h2.m) {
        return 0;
    }
    else if (h1.h > h2.h || (h1.h == h2.h && h1.m > h2.m)) {

        return 1;
    }
    else if (h1.h < h2.h || (h1.h == h2.h && h1.m < h2.m)) {

        return -1;
    }
    else return 2;
}

void initDate(Date& date, int j, int m, int a) {

    date.jour = j;
    date.mois = m;
    date.annee = a;

}

int dateComp(Date& d1, Date& d2) {

    if (d1.jour == d2.jour && d1.mois == d2.mois && d1.annee == d2.annee) {
        return 0;
    }
    else if (d1.annee > d2.annee || (d1.annee == d2.annee && d1.mois > d2.mois || (d1.annee == d2.annee && d1.mois == d2.mois && d1.jour > d2.jour))) {
        return 1;
    }
    else if (d1.annee < d2.annee || (d1.annee == d2.annee && d1.mois < d2.mois || (d1.annee == d2.annee && d1.mois == d2.mois && d1.jour < d2.jour))) {
        return -1;
    }
    else return 2;

}

void initEvenement(Evenement& e, const char titre[], int jour, int mois, int annee, int heure_debut, int minute_debut, int duree) {

    if (strlen(titre) > 50) return;

    strcpy_s(e.titre, titre);
    e.date.jour = jour;
    e.date.mois = mois;
    e.date.annee = annee;
    e.horaire.h = heure_debut;
    e.horaire.m = minute_debut;
    e.duree = duree;

}

void initEvenement(Evenement& e, const char titre[], int jour, int mois, int annee, int heure_debut, int minute_debut, int heure_fin, int minute_fin){
    
    Horaire h1, h2;

    h1.h = heure_debut;
    h1.m = minute_debut;
    h2.h = heure_fin;
    h2.m = minute_fin;

    if (horComp(h1, h2) == 1) return;

    int duree = abs((h1.h * 60 + h1.m) - (h2.h * 60 + h2.m));

    strcpy_s(e.titre, titre);
    e.date.jour = jour;
    e.date.mois = mois;
    e.date.annee = annee;
    e.horaire.h = heure_debut;
    e.horaire.m = minute_debut;
    e.duree = duree;

}

void afficheEvenement(Evenement& e) {

    cout << e.titre << endl;
    if (e.date.mois > 9) {

        cout << "Date : " << e.date.jour << "/" << e.date.mois << "/" << e.date.annee << endl;
    }
    else {
        cout << "Date : " << e.date.jour << "/" << "0" << e.date.mois << "/" << e.date.annee << endl;
    }
    
    cout << "Horaire : " << e.horaire.h << "h" << e.horaire.m << endl;
    cout << "Duree : " << e.duree << " minutes" << endl;
    
}

void copieEvenement(Evenement& dest, Evenement& source) {

    strcpy_s(dest.titre, source.titre);
    dest.date.jour = source.date.jour;
    dest.date.mois = source.date.mois;
    dest.date.annee = source.date.annee;
    dest.horaire.h = source.horaire.h;
    dest.horaire.m = source.horaire.m;
    dest.duree = source.duree;

}

bool ajouterEvenement(Evenement agenda[], int& compteur, Evenement& e) {
    
    if (compteur > TAILLE - 1) {
        return false;
    }

    for (int i = 0; i < compteur; i++) {

        if (horComp(e.horaire, agenda[i].horaire) == 0 && dateComp(e.date, agenda[i].date) == 0) return false;
        if (horComp(e.horaire, agenda[i].horaire) == 1 && dateComp(e.date, agenda[i].date) == 0) {

            int minutes = agenda[i].duree + (agenda[i].horaire.h * 60) + agenda[i].horaire.m;
            int heurefinal = minutes / 60;
            int minutesfinal = minutes % 60;
            Horaire h1;

            h1.h = heurefinal;
            h1.m = minutesfinal;

            if (horComp(h1, e.horaire) == 1) return false;

        }
        if (horComp(e.horaire, agenda[i].horaire) == -1 && dateComp(e.date, agenda[i].date) == 0) {

            int minutes = e.duree + (e.horaire.h * 60) + e.horaire.m;
            int heurefinal = minutes / 60;
            int minutesfinal = minutes % 60;
            Horaire h1;

            h1.h = heurefinal;
            h1.m = minutesfinal;

            if (horComp(h1, agenda[i].horaire) == 1) return false;

        }
        


    }

    copieEvenement(agenda[compteur], e);
    compteur++;
    return true;
}

void afficheAgenda(Evenement Agenda[], int n) {
    for (int i = 0; i < n; i++) {
        afficheEvenement(Agenda[i]);
        cout << endl;
    }
}

void echangeEvent(Evenement& Agenda1, Evenement& Agenda2) {
    
    Evenement tmp;
    copieEvenement(tmp, Agenda1);
    copieEvenement(Agenda1, Agenda2);
    copieEvenement(Agenda2, tmp);

}

void Tri(Evenement Agenda[], int n) {

    int inc = 1;
    
    while (inc != 0) {
        inc = 0;
        for (int i = 0; i < n - 1; i++) {

            if (dateComp(Agenda[i].date, Agenda[i + 1].date) == 1) {
                inc = 1;
                echangeEvent(Agenda[i], Agenda[i + 1]);
            }
            else if (horComp(Agenda[i].horaire, Agenda[i + 1].horaire) == 1 && dateComp(Agenda[i].date, Agenda[i + 1].date) == 0) {
                inc = 1;
                echangeEvent(Agenda[i], Agenda[i + 1]);
            }
        }
    }

}

bool supprimerEvenement(Evenement agenda[], int& compteur, const char titre[], Date& d) {
    for (int i = 0; i < compteur; i++) {

        if (strcmp(agenda[i].titre, titre) == 0 && dateComp(agenda[i].date, d) == 0) {


            strcpy_s(agenda[i].titre, " ");
            agenda[i].date.jour = 0;
            agenda[i].date.mois = 0;
            agenda[i].date.annee = 0;
            agenda[i].horaire.h = 0;
            agenda[i].horaire.m = 0;

            compteur--;
            echangeEvent(agenda[i], agenda[compteur]);
            
            return true;
        }

    }
    return false;
}

void exportHTML(Evenement Agenda[], int n) {

    ofstream sortie("agenda.html", ios::trunc);
    if (!sortie)
        cout << "Probleme d'ouverture " << endl;
    else {
        
        sortie << "<html>\n<head><title>MON AGENDA PERSONNEL</title></head>\n<body>\n<h1><center>MON AGENDA PERSONNEL</center></h1>\n<table border = \"1\" align = \"center\">\n<tr>\n<th>Date</th>\n<th>Nom</th>\n<th>Heure debut</th>\n<th>Heure fin</th><br/>\n</tr>";


        for (int i = 0; i < n; i++) {
            
            if ( i != 0 && dateComp(Agenda[i].date, Agenda[i-1].date) != 0){
                if (Agenda[i].date.mois == 1) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " janvier " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 2) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " fevrier " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 3) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " mars " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 4) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " avril " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 5) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " mai " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 6) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " juin " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 7) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " juillet " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 8) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " aout " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 9) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " septembre " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 10) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " octobre " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 11) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " novembre " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 12) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " decembre " << Agenda[i].date.annee << "</td>" << endl;
                }
            }
            else if (i == 0) {

                if (Agenda[i].date.mois == 1) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " janvier " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 2) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " fevrier " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 3) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " mars " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 4) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " avril " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 5) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " mai " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 6) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " juin " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 7) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " juillet " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 8) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " aout " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 9) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " septembre " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 10) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " octobre " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 11) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " novembre " << Agenda[i].date.annee << "</td>" << endl;
                }
                else if (Agenda[i].date.mois == 12) {
                    sortie << "<tr>\n<td>" << Agenda[i].date.jour << " decembre " << Agenda[i].date.annee << "</td>" << endl;
                }

            }
            else {
                sortie << "<tr>\n<td>" << "  " << "</td>" << endl;
            }

            sortie << "<td>" << Agenda[i].titre << "</td>" << endl;

            if (Agenda[i].horaire.m < 10) {
                sortie << "<td>" << Agenda[i].horaire.h << ":0" << Agenda[i].horaire.m << "</td>" << endl;
            }
            else {
                sortie << "<td>" << Agenda[i].horaire.h << ":" << Agenda[i].horaire.m << "</td>" << endl;
            }

            int minutes = Agenda[i].duree + (Agenda[i].horaire.h * 60) + Agenda[i].horaire.m;
            int heurefinal = minutes / 60;
            int minutesfinal = minutes % 60;

            if (minutesfinal < 10) {
                sortie << "<td>" << heurefinal << ":0" << minutesfinal << "</td>" << endl;
            }
            else {
                sortie << "<td>" << heurefinal << ":" << minutesfinal << "</td>" << endl;
            }

        }



        sortie << "\n</table><br/>";
        sortie.close();
    }



}


int main() {
    
    Evenement t[TAILLE];
    Evenement e;
    Date date;
    int n = 0;

    initEvenement(e, "Soiree reveillon", 1, 1, 2017, 1, 0, 9, 0);
    ajouterEvenement(t, n, e);
    initEvenement(e, "RDV medecin", 12, 10, 2016, 8, 0, 120);
    ajouterEvenement(t, n, e);
    initEvenement(e, "TP algo", 12, 11, 2016, 14, 0, 120);
    ajouterEvenement(t, n, e);
    initEvenement(e, "Soutien", 12, 11, 2016, 11, 0, 90);
    ajouterEvenement(t, n, e);
    initEvenement(e, "Resto avec Pauline", 12, 11, 2016, 12, 45, 14, 0);
    ajouterEvenement(t, n, e);
    initEvenement(e, "CM Reseau", 11, 12, 2016, 11, 0, 90);
    ajouterEvenement(t, n, e);

    //ne doivent pas être visibles à la fin car supprimés plus loin
    initEvenement(e, "erreur1", 12, 8, 2016, 7, 0, 240);
    ajouterEvenement(t, n, e);
    initEvenement(e, "erreur2", 13, 8, 2016, 7, 0, 240);
    ajouterEvenement(t, n, e);
    //ne doit pas s'ajouter (recouvrement avec rdv medecin)
    initEvenement(e, "erreur3", 12, 10, 2016, 9, 0, 30);
    ajouterEvenement(t, n, e);
    //ne doit pas s'ajouter (recouvrement avec rdv medecin)
    initEvenement(e, "erreur4", 12, 10, 2016, 9, 0, 120);
    ajouterEvenement(t, n, e);
    //ne doit pas s'ajouter (recouvrement avec rdv medecin)
    initEvenement(e, "erreur5", 12, 10, 2016, 7, 0, 120);
    ajouterEvenement(t, n, e);
    //ne doit pas s'ajouter (recouvrement avec rdv medecin)
    initEvenement(e, "erreur6", 12, 10, 2016, 7, 0, 240);
    ajouterEvenement(t, n, e);
    //ne doit pas s'ajouter (recouvrement avec erreur1)
    initEvenement(e, "erreur7", 12, 8, 2016, 10, 0, 240);
    ajouterEvenement(t, n, e);

    //suppression de erreur1
    initDate(date, 12, 8, 2016);
    supprimerEvenement(t, n, "erreur1", date);
    //suppression d'un événement n'existant pas (mauvais titre)
    initDate(date, 12, 10, 2016);
    supprimerEvenement(t, n, "RDV docteur", date);
    //suppression d'un événement n'existant pas (mauvaise date)
    initDate(date, 12, 10, 2015);
    supprimerEvenement(t, n, "RDV medecin", date);
    //2 suppressions successives du même événement
    initDate(date, 13, 8, 2016);
    supprimerEvenement(t, n, "erreur2", date);
    supprimerEvenement(t, n, "erreur2", date);

    initEvenement(e, "Resto avec Alain", 12, 8, 2017, 12, 45, 14, 0);
    ajouterEvenement(t, n, e);
    initEvenement(e, "Repas grand maman", 1, 1, 2017, 12, 0, 110);
    ajouterEvenement(t, n, e);


    Tri(t, n);
    afficheAgenda(t, n);
    exportHTML(t, n);

    return 0;

}