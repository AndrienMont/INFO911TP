INFO911 TP : Segmentation temps-réel semi-supervisée par distance d'histogramme de couleurs

Andrien Montmayeur

Le but de ce TP est de segmenter un flux vidéo en temps réel en utilisant les distances entre des histogrammes de couleurs.
Le programme va capturer un flux vidéo à travers la webcam de l'ordinateur et l'afficher dans une fenêtre.
Les différents traitements seront visibles sur cette fenêtre.
On peut effectuer différentes actions sur le flux :
- Si on appuie sur la touche 'f', le flux est gelé. Il suffit de rappuyer pour le dégeler.
- Si on appuie sur la touche 'v', l'image est coupée en deux. On calcule ensuite la distance entre l'histogramme de la partie gauche et de la partie droite du flux
- Si on appuie sur la touche 'b', l'histogramme du flux est stocké dans un vecteur servant à déterminer le fond.
- Si on appuie sur la touche 'a', l'histogramme du flux est stocké dans un vecteur servant à déterminer les objets.
- Si on appuie sur la touche 'r', on passe en mode "reconnaissance d'objets", où les vecteurs de fond et d'objets sont utilisés pour déterminer si un pixel appartient à l'objet ou au fond.
- Si on appuie sur la touche 'q', le programme s'arrête.

Développements ajoutés:
- Possibilité d'ajouter plusieurs objets : en appuyant sur la touche 'n', on peut stocker plusieurs histogrammes d'objets, qui sont ensuite utilisés dans la reconnaissance. Cela permet d'avoir différentes couleurs en fonction du nombre d'objets + 1 (en comptant le fond).
- 