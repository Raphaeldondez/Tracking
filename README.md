# L'objectif de ce projet est de réaliser un système de tracking d'une personne dans une pièce afin d'en connaître la position.

1) Méthode : On va constituer une tête composée de 2 capteurs de distance à ultrason afin de connaitre la distance à droite
        de la position pointée et celle à gauche de cette position.
        Si il y a un objet à droite mais pas à gauche alors on tourne la tête vers la gauche (de même pour la droite).
        On gardera en mémoire l'angle ainsi que la distance de la position pointée.    


2) Matériel : -Une carte arduino UNO sera utilisée pour le traitement des données.
              -On va utiliser 2 capteurs de distances ultrason.
              -On prendra un moteur servo asservit en position pour le contrôle de l'angle.
              -Un laser sera utilisé pour s'assurer de la position pointée.
