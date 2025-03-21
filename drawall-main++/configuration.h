#ifndef CONFIGURATION_H
#define CONFIGURATION_H


class configuration
{
public:
    configuration();
    float mesureA = 65; //distance horizontale entre le point A et le point C
    float mesureB = 65; //distance horizontale entre le point B et le point C
    float mesureC = 75; // distance verticale entre le C et les points A et B
    float mesureD = 900; // distance entre moteur
    float deportx = -35; // déport crayon x par rapport au point C
    float deporty = -15 ; // déport crayon y par rapport au point c
    //float deportx = 0; // déport crayon x par rapport au point C
    //float deporty = 0 ; // déport crayon y par rapport au point c
    float margeDroite_x = 105;
    float margeDroite_y = 140;
    float margeGauche_x = 105;
    float margeGauche_y = 140;
    float hauteur = 860; // hauteur tableau
    float largeur = 880; //largeur tableau
};

#endif // CONFIGURATION_H
