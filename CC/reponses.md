---
lang      : fr
title     : Contrôle de connaissances SE207 "SystemC"
date      : 17 juin 2020
---

# Instructions

Ce contrôle de connaissances est strictement individuel.
Vous devez modifier ce fichier pour y inclure vos réponses puis l'ajouter à votre dépôt dans un dossier `CC` à la racine de ce dernier.

- Seules les parties entre *`---`* sont à modifier.

- Laissez une ligne vide avant et après chaque *`---`*.

# Questions

### Question 1

1. Quels types pouvez-vous utiliser en SystemC pour représenter des entiers?
1. Quels critères vous feraient choisir un type plutôt qu'un autre ?
1. Quelles implications sur les performances de la simulation?

---



1. On peut utiliser les types suivants : `sc_int<N>`(entier), `sc_uint<N>` (entier non signé) avec N qui désigne le nombre de bits. 

   On peut aussi utiliser les vecteurs : `sc_bv<N>` ou `sc_lv<N>` qui sont respectivement les vecteurs de bits et les vecteurs logique.

2. La différence entre `sc_bv<N>`et `sc_int<N>` réside dans le fait que les types `sc_int`sont surchargées d'opérateurs qui rendent leur utilisation facile.

   Donc si on veut faire des calculs avec des entiers il faut mieux utiliser `sc_int `ou `sc_uint` mais pour des opérations bits à bits, `sc_bv` est suffisant.

3. Le type `sc_lv`demande plus de place (deux fois plus en fait) pour être stocké car il contient 4 bits 0, 1, Z, X. 

   Concernant les entiers qui sont d'une taille classique (par exemple 8, 16, 32, 64) , il vaut mieux utiliser les structures de C++ ( par exemple `int`) qui implémentent plus efficacement les opérations arithmétiques.

   

---

### Question 2

1. Pourquoi, contrairement aux autres langages HDL, SystemC vous impose l'utilisation d'un type particulier pour pouvoir faire des affectations différées?
1. Quel est ce type? Et expliquez brièvement comment ces affectations différées sont mises en œuvre dans la bibliothèque.
1. Dans quels cas l'utilisation d'affectations différées est-elle nécessaire?

---



1. SystemC impose l'utilisation d'un type particulier parce que c'est un langage qui permet de simuler les affectations qui surviennent au bout d'un cycle. En C++ qui n'est pas un langage conçu pour la simulation, il n'y a pas de tel type car la plupart des personnes codant en C++ n'en auraient pas l'utilité. 

2. C'est le type `sc_signal` qui permet de créer des signaux qui permettent les affectations différées. 

   La structure de ce type est : `sc_signal<TYPE_DE_LA_VARIABLE>` donc ça peut être par exemple `sc_signal<bool>` que l'on utilise souvent en simulation.

   Pour mettre en oeuvre ces affectations il y a 3 fonctions. Les fonctions `read`, `write` et `update`. La fonction `read `permet de voir la valeur actuelle du signal. La fonction `write` permet de modifier la valeur future du signal (celle qui sera changée à la fin du cycle). Et la fonction `update` permet de mettre à jour la valeur actuelle qui prend la valeur de la valeur future.

3. Cela est utile par exemple pour les signaux de contrôle, quand est-ce qu'un module est prêt à échanger par exemple et cela permet de se synchroniser sur le signal d'horloge.



---


### Question 3

Nous voulons modéliser un système de temporisation synchrone ayant les caractéristiques suivantes:

- une horloge `clk` et un signal de remise à zéro asynchrone `nrst` actif sur niveau bas,
- une entrée sur 1 bit `go`,
- une sortie sur 4 bits initialement à 0.

À chaque fois que `go` passe à 1 la sortie effectue la séquence suivante:

- incrémente de 0 à 11,
- patiente 7 cycles,
- décrémente de 11 à 0 puis s'arrête.

1. Écrire le code de deux module SystemC reproduisant ce comportement:

   * le premier contiendra un **`SC_THREAD`** pour une description "cycle accurate",
   * le second contiendra une ou plusieurs **`SC_METHOD`** pour une description RTL.

---

```{.cpp}

// En utilisant un SC_THREAD
SC_MODULE(SeqThread) {
  sc_in<bool> clk;
  sc_in<bool> nrst;
  sc_in<bool> go;
  
  sc_out<sc_int<4>> out;
  
  SC_CTOR(SeqThread): clk("clk"), out("out") {
    SC_THREAD(incr);
    sensitive << clk.pos();
    async_reset_signal_is(nrst, false);
  }
	
	void inc(){
	
		out = 0;
		wait();
		
		while(1){
			if (go){
				for (int i = 0; i++; i<12){
					out++;
					wait();
				}
				for (int i = 0; i++; i<8){
					wait();
				}
				for (int i = 0; i++; i<12){
					out--;
					wait();
				}
			}
		}
	}
}}
}

// En utilisant une ou plusieurs SC_METHOD
SC_MODULE(SeqMethod) {
  sc_in<bool> clk;
  sc_in<bool> nrst;
  sc_in<bool> go;
...
}

```

---


### Question 4

1. Expliquez pourquoi les **`SC_THREAD`** contiennent souvent une boucle infinie ?
   * Que se passe-t-il si cette boucle n'existe pas ?
1. Donnez un exemple d'utilisation pratique où cette boucle n'est pas nécessaire.

---

...

---

### Question 5

Deux processus servent à modéliser deux composants matériels qui fonctionnent à tour de rôle.
Pour modéliser ce comportement, nous pouvons utiliser des `sc_fifo`.

1. Donnez, **dans les grandes lignes**, un exemple de code illustrant le fonctionnement **cyclique** suivant:
    * le premier module effectue une action,
    * il passe la main au second et attend,
    * le second module prend la main et effectue une action,
    * il repasse la main au premier et attend,

**Précisez le type des processus utilisés**

---

```{.cpp}
// premier processus
void P1() {
}

// second processus
void P2() {
}
```

---


Nous voulons un modèle plus précis temporellement et nous ajoutons un signal d'horloge `clk` dont le front montant est ajouté à la liste de sensibilité des deux processus.

1. Pensez-vous que la synchronisation des deux processus garantisse que le modèle reste synchrone (*justifiez votre réponse*)?

1. Proposez une autre méthode de synchronisation qui garantisse le synchronisme.
    * Quelles implications sur la vitesse de la simulation par rapport à l'utilisation de la `sc_fifo`?

---

...

---

