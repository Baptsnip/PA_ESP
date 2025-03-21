#include "vitrine.h"

vitrine::vitrine(float distance_moteur, float marge_horizontale, float marge_verticale, float hauteur, float largeur)
{
    _D = distance_moteur;
    _E = marge_verticale;
    _F = marge_horizontale;
    _G = largeur;
    _H = hauteur;
}
