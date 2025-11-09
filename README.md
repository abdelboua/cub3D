# CUB3D - Raycasting Game Engine

## 📖 Table des matières
1. [Introduction](#introduction)
2. [Théorie du Raycasting](#théorie-du-raycasting)
3. [Architecture du projet](#architecture-du-projet)
4. [Documentation des fonctions](#documentation-des-fonctions)
5. [Compilation et utilisation](#compilation-et-utilisation)

---

## Introduction

**Cub3D** est un projet inspiré du célèbre jeu **Wolfenstein 3D** (1992), le premier FPS de l'histoire. Ce projet utilise la technique du **raycasting** pour créer une vue 3D à partir d'une carte 2D.

### Objectifs pédagogiques :
- Comprendre les mathématiques derrière le raycasting
- Manipuler la MinilibX (bibliothèque graphique)
- Gérer les événements clavier et le rendu en temps réel
- Parser des fichiers de configuration
- Gérer la mémoire et les erreurs

---

## Théorie du Raycasting

### Principe de base

Le **raycasting** est une technique de rendu 3D simplifiée qui projette des rayons depuis la position du joueur dans la direction de sa vue. Pour chaque colonne de pixels à l'écran, on lance un rayon et on calcule :
1. La distance jusqu'au premier mur rencontré
2. La hauteur à dessiner en fonction de cette distance
3. La texture à appliquer selon l'orientation du mur

### Formules mathématiques clés

#### 1. Direction du rayon
Pour chaque colonne `x` de l'écran :
```
camera_x = 2 * x / WIDTH - 1
ray_dir_x = dir_x + fov_x * camera_x
ray_dir_y = dir_y + fov_y * camera_x
```

#### 2. Algorithme DDA (Digital Differential Analyzer)
Calcul de la distance entre deux intersections consécutives :
```
delta_dx = |1 / ray_dir_x|
delta_dy = |1 / ray_dir_y|
```

#### 3. Distance au mur (correction de la distorsion fisheye)
```
Si side == 0 (mur vertical) :
    dist_wall = (map_x - pos_x + (1 - step_x) / 2) / ray_dir_x
Sinon (mur horizontal) :
    dist_wall = (map_y - pos_y + (1 - step_y) / 2) / ray_dir_y
```

#### 4. Hauteur du mur à l'écran
```
line_height = HEIGHT / dist_wall
```

### Système de coordonnées

```
    N (North)
    ↑
    |
W ← · → E (East/West)
    |
    ↓
    S (South)

Direction player:
- dir_x, dir_y : vecteur de direction (regard)
- fov_x, fov_y : vecteur du plan caméra (perpendiculaire à dir)

Exemple pour direction NORD:
- dir_x = 0,  dir_y = -1
- fov_x = 0.66, fov_y = 0  (FOV de 66°)
```

---

## Architecture du projet

```
cub3d/
├── header.h                 # Structures et prototypes
├── main.c                   # Point d'entrée et boucle principale
├── init.c                   # Initialisation des données
├── event.c                  # Gestion des événements clavier
├── move.c                   # Déplacement et rotation du joueur
├── raycasting.c             # Algorithme de raycasting
├── draw_wall.c              # Rendu des murs texturés
├── render.c                 # Affichage fond et pixels
├── textures.c               # Chargement des textures
├── parse_file.c             # Parsing du fichier .cub
├── parse_texture.c          # Extraction des chemins de textures
├── parse_color.c            # Extraction des couleurs RGB
├── parse_map.c              # Lecture de la carte
├── map_validation.c         # Validation de la carte
├── map_walls.c              # Vérification des murs
├── utils1.c                 # Fonctions utilitaires
├── libft/                   # Bibliothèque personnelle
├── get_next_line/           # Lecture ligne par ligne
└── minilibx-linux/          # Bibliothèque graphique
```

---

## Documentation des fonctions

### 📁 main.c

#### `int main(int ac, char **av)`
**Rôle :** Point d'entrée du programme
**Processus :**
1. Vérifie les arguments (doit recevoir un fichier .cub)
2. Initialise les structures de données
3. Parse le fichier de configuration
4. Initialise MLX et crée la fenêtre
5. Charge les textures
6. Configure les hooks d'événements
7. Lance la boucle de jeu

#### `int gameloop(t_datagame *data)`
**Rôle :** Boucle principale exécutée à chaque frame
**Processus :**
1. Calcule le delta_time (temps écoulé depuis la dernière frame)
2. Met à jour la position du joueur selon les touches pressées
3. Dessine le fond (ciel + sol)
4. Lance tous les rayons pour dessiner les murs
5. Affiche l'image à l'écran

**Théorie :** Le delta_time permet d'avoir un mouvement fluide indépendant de la vitesse de la machine.

#### `int close_window(t_datagame *data)`
**Rôle :** Libère toutes les ressources et ferme proprement le programme
**Processus :**
- Détruit les images (frame buffer + textures)
- Détruit la fenêtre et la connexion MLX
- Libère la mémoire allouée

---

### 📁 init.c

#### `void init_data(t_datagame *data)`
**Rôle :** Initialise tous les champs de la structure principale à des valeurs par défaut
**Important :** Met tous les pointeurs à NULL pour éviter les segfaults lors de la libération

#### `void init_player(t_datagame *data)`
**Rôle :** Configure la position et l'orientation initiale du joueur
**Théorie mathématique :**
- Position centrée sur la case : `pos_x = player_x + 0.5`
- Direction et FOV selon l'orientation (N/S/E/W)
- Le FOV est perpendiculaire à la direction (produit vectoriel)

**Exemple pour Nord :**
```c
dir_y = -1    // Regarde vers le haut
dir_x = 0
fov_x = 0.66  // Plan caméra horizontal
fov_y = 0
```

---

### 📁 event.c

#### `void init_keys(t_keys *keys)`
**Rôle :** Initialise toutes les touches à 0 (non pressées)

#### `int press_key(int keycode, t_datagame *data)`
**Rôle :** Détecte quand une touche est pressée et met son flag à 1
**Touches supportées :**
- W/S : Avancer/Reculer
- A/D : Strafe gauche/droite
- ←/→ : Rotation
- ESC : Quitter

#### `int release_key(int keycode, t_datagame *data)`
**Rôle :** Détecte quand une touche est relâchée et met son flag à 0
**Théorie :** Ce système de flags permet un mouvement fluide et simultané (ex: avancer + tourner)

---

### 📁 move.c

#### `static void player_move(t_datagame *data, double speed, int forward)`
**Rôle :** Déplace le joueur vers l'avant ou l'arrière
**Théorie mathématique :**
```c
new_x = pos_x + dir_x * speed  (si forward)
new_y = pos_y + dir_y * speed
```
**Collision :** Vérifie que la nouvelle position est un '0' (espace vide) avant de bouger

#### `static void player_strafe(t_datagame *data, double speed, int right)`
**Rôle :** Déplace le joueur latéralement (perpendiculairement à sa direction)
**Théorie :** Utilise le vecteur FOV (perpendiculaire à dir) pour le mouvement latéral
```c
new_x = pos_x + fov_x * speed
new_y = pos_y + fov_y * speed
```

#### `static void rotate_player(t_datagame *data, double rot, int clockwise)`
**Rôle :** Fait pivoter la direction et le plan caméra du joueur
**Théorie mathématique - Rotation 2D :**
```c
Matrice de rotation :
[ cos(θ)  -sin(θ) ]
[ sin(θ)   cos(θ) ]

Application :
new_dir_x = dir_x * cos(angle) - dir_y * sin(angle)
new_dir_y = dir_x * sin(angle) + dir_y * cos(angle)
```
**Important :** Le plan caméra (FOV) doit tourner en même temps !

#### `void update_player(t_datagame *data, double delta_time)`
**Rôle :** Fonction principale appelée chaque frame pour gérer tous les mouvements
**Théorie du delta_time :**
```
move_speed = base_speed * delta_time
```
Cela garantit que la vitesse est indépendante du framerate :
- Machine rapide (100 FPS) : delta_time petit → petits déplacements fréquents
- Machine lente (30 FPS) : delta_time grand → grands déplacements rares
→ **Même vitesse perçue**

---

### 📁 raycasting.c

#### `void init_ray_data(t_datagame *data, int x)`
**Rôle :** Initialise les données pour le rayon de la colonne `x`
**Théorie :**
1. `camera_x` : Position sur le plan caméra (-1 à +1)
2. `ray_dir_x/y` : Direction du rayon = direction joueur + offset selon camera_x
3. `map_x/y` : Case de départ (position joueur arrondie)
4. `delta_dx/dy` : Distance à parcourir pour traverser une case entière

**Formules clés :**
```c
camera_x = 2 * x / WIDTH - 1
ray_dir_x = dir_x + fov_x * camera_x
delta_dx = |1 / ray_dir_x|
```

#### `void init_ray_step_sidedist(t_datagame *data)`
**Rôle :** Calcule la direction du pas (±1) et la distance jusqu'à la première intersection
**Théorie :**
- `step_x/y` : Direction du rayon (+1 ou -1) sur chaque axe
- `sidedist_x/y` : Distance depuis la position actuelle jusqu'à la prochaine ligne de grille

**Exemple :**
```
Si ray_dir_x < 0 (rayon va vers la gauche) :
- step_x = -1
- sidedist_x = (pos_x - map_x) * delta_dx
```

#### `void dda(t_datagame *data)`
**Rôle :** Algorithme DDA pour trouver le premier mur touché
**Théorie DDA (Digital Differential Analyzer) :**
1. Compare `sidedist_x` et `sidedist_y`
2. Avance d'une case dans la direction la plus proche
3. Met à jour la distance parcourue
4. Répète jusqu'à toucher un mur ('1')

**Pourquoi ça marche :**
On avance toujours vers l'intersection la plus proche, garantissant qu'on ne saute aucun mur.

#### `void calculate_wall_height(t_datagame *data)`
**Rôle :** Calcule la distance réelle au mur et la hauteur à dessiner
**Théorie - Correction fisheye :**
```c
Si on mesure juste la distance euclidienne, on obtient une distorsion "fisheye".
Solution : mesurer la distance perpendiculaire au plan caméra.

dist_wall = (map_x - pos_x + (1 - step_x)/2) / ray_dir_x
```
**Calcul de la hauteur :**
```c
line_height = HEIGHT / dist_wall
```
Plus le mur est loin, plus il est petit à l'écran.

**Limites d'affichage :**
```c
start_draw = -line_height/2 + HEIGHT/2  (centre l'écran)
end_draw = line_height/2 + HEIGHT/2
```
On clippe à [0, HEIGHT-1] pour rester dans l'écran.

#### `void cast_all_rays(t_datagame *data)`
**Rôle :** Lance un rayon pour chaque colonne de l'écran (800 rayons pour WIDTH=800)
**Processus :**
```c
Pour x de 0 à WIDTH-1 :
    1. Initialiser le rayon
    2. Calculer step et sidedist
    3. DDA pour trouver le mur
    4. Calculer hauteur du mur
    5. Dessiner la colonne texturée
```

---

### 📁 draw_wall.c

#### `static t_img *get_wall_texture(t_datagame *data)`
**Rôle :** Détermine quelle texture appliquer selon l'orientation du mur touché
**Logique :**
```c
Si side == 0 (mur vertical - axe X) :
    Si ray_dir_x > 0 → Mur EST
    Sinon → Mur OUEST
Sinon (mur horizontal - axe Y) :
    Si ray_dir_y > 0 → Mur SUD
    Sinon → Mur NORD
```

#### `static int calculate_tex_x(t_datagame *data, t_img *texture)`
**Rôle :** Calcule la coordonnée X sur la texture (quelle colonne de pixels utiliser)
**Théorie :**
1. Calculer `wall_x` : position exacte de l'impact sur le mur (0.0 à 1.0)
2. Convertir en coordonnée texture : `tex_x = wall_x * texture_width`
3. Inverser si nécessaire selon l'orientation pour éviter les textures miroir

**Formule wall_x :**
```c
Si mur vertical :
    wall_x = pos_y + dist_wall * ray_dir_y
Sinon :
    wall_x = pos_x + dist_wall * ray_dir_x
wall_x = wall_x - floor(wall_x)  // Garde seulement la partie décimale
```

#### `static void render_wall_stripe(t_datagame *data, t_img *texture, int x, int tex_x)`
**Rôle :** Dessine une colonne verticale de mur avec texture
**Théorie du mapping de texture :**
```c
step = texture_height / line_height
```
Cette valeur détermine combien on avance dans la texture pour chaque pixel d'écran.

**Assombrissement des côtés :**
```c
if (side == 1)
    color = (color >> 1) & 8355711;
```
Divise les composantes RGB par 2 pour les murs horizontaux (effet de lumière)

#### `void draw_wall_column(t_datagame *data, int x)`
**Rôle :** Fonction principale qui orchestre le rendu d'une colonne
**Processus :**
1. Sélectionner la bonne texture
2. Calculer la coordonnée X sur la texture
3. Dessiner la bande verticale pixel par pixel

---

### 📁 render.c

#### `void put_pixel(t_datagame *data, int x, int y, int color)`
**Rôle :** Écrit un pixel dans le buffer d'image
**Théorie MLX - Accès direct à la mémoire :**
```c
pixel = addr + (y * line_len + x * (bpp / 8))
```
- `line_len` : Taille d'une ligne en bytes (peut inclure du padding)
- `bpp` : Bits per pixel (généralement 32)
- On cast en `unsigned int*` pour écrire la couleur directement

**Vérification de limites :** Évite d'écrire hors de l'image (segfault)

#### `int draw_background(t_datagame *data)`
**Rôle :** Dessine le plafond et le sol avant de dessiner les murs
**Processus :**
```c
Pour y de 0 à HEIGHT/2 :
    Dessiner ceiling_color (plafond)
Pour y de HEIGHT/2 à HEIGHT :
    Dessiner floor_color (sol)
```
**Optimisation possible :** Utiliser `mlx_clear_window` ou `memset` serait plus rapide

---

### 📁 textures.c

#### `static int load_one_texture(t_datagame *data, t_img *texture, char *path)`
**Rôle :** Charge un fichier .xpm en mémoire
**Processus MLX :**
1. `mlx_xpm_file_to_image` : Charge le fichier et retourne un pointeur d'image
2. `mlx_get_data_addr` : Obtient l'adresse mémoire des pixels
3. Stocke width, height, bpp, line_len pour accès ultérieur

**Gestion d'erreur :** Vérifie que le fichier existe et est valide

#### `int init_textures(t_datagame *data)`
**Rôle :** Charge les 4 textures (NO, SO, EA, WE) au démarrage
**Important :** Appelée une seule fois au lancement, évite de recharger à chaque frame

#### `int get_texture_color(t_img *tex, int x, int y)`
**Rôle :** Lit la couleur d'un pixel (x, y) dans une texture
**Théorie :**
```c
pixel = addr + (y * line_len + x * (bpp / 8))
color = *(int*)pixel
```
Retourne un int au format 0xRRGGBB

**Protection :** Retourne noir si (x, y) est hors limites

---

### 📁 parse_file.c

#### `int parse_file(char *filename, t_datagame *data)`
**Rôle :** Fonction principale de parsing du fichier .cub
**Architecture :**
1. Ouvre le fichier
2. Lit ligne par ligne avec get_next_line
3. Identifie le type de ligne (config ou map)
4. Délègue le traitement à des fonctions spécialisées
5. Valide que tous les éléments requis sont présents

**Format attendu :**
```
NO ./textures/north.xpm
SO ./textures/south.xpm
EA ./textures/east.xpm
WE ./textures/west.xpm
F 220,100,0
C 225,30,0

111111
100001
101101
100N01
111111
```

#### `static int process_file_lines(int fd, t_datagame *data)`
**Rôle :** Boucle sur les lignes du fichier et les traite
**Logique :**
- Ligne vide → Ignorée
- Ligne config (NO, SO, F, C...) → Parsée et stockée
- Première ligne de map → Sauvegardée et boucle arrêtée

#### `static int finalize_parsing(t_datagame *data, int fd)`
**Rôle :** Vérifie la configuration et parse la carte complète
**Validation :**
- 6 éléments obligatoires : NO, SO, EA, WE, F, C
- Appelle `parse_map` pour lire toutes les lignes de la map
- Appelle `valid_map` pour vérifier la cohérence

---

### 📁 parse_texture.c

#### `int parse_texture_no(char *line, t_datagame *data)`
#### `int parse_texture_so(char *line, t_datagame *data)`
#### `int parse_texture_ea(char *line, t_datagame *data)`
#### `int parse_texture_we(char *line, t_datagame *data)`
**Rôle :** Extrait le chemin vers un fichier de texture
**Format attendu :** `NO ./path/to/texture.xpm`
**Processus :**
1. Skip l'identifiant (NO, SO...)
2. Skip les espaces
3. Extrait le chemin
4. Supprime le `\n` final
5. Vérifie que la texture n'a pas déjà été définie
6. Incrémente `config_elements_read`

---

### 📁 parse_color.c

#### `int parse_fcolor(char *line, t_datagame *data)`
#### `int parse_ccolor(char *line, t_datagame *data)`
**Rôle :** Parse une couleur au format `F 220,100,0` (RGB)
**Processus :**
1. Skip l'identifiant (F ou C)
2. Parse les 3 composantes RGB avec `ft_atoi`
3. Vérifie que chaque valeur est entre 0 et 255
4. Encode en int : `(R << 16) | (G << 8) | B`
5. Stocke dans `floor_color` ou `ceiling_color`

**Format de stockage :**
```
0x00RRGGBB
```

---

### 📁 parse_map.c

#### `int parse_map(char *first_line, int fd, t_datagame *data)`
**Rôle :** Lit toutes les lignes de la map et les stocke dans un tableau
**Processus :**
1. Crée une liste chaînée temporaire (facilite l'ajout dynamique)
2. Ajoute `first_line` (déjà lue)
3. Lit les lignes restantes avec get_next_line
4. Convertit la liste en tableau 2D
5. Calcule map_width (ligne la plus longue) et map_height

**Pourquoi une liste → tableau :**
- Liste : Ajout dynamique facile
- Tableau : Accès rapide par index (map[y][x])

---

### 📁 map_validation.c

#### `int valid_map(t_datagame *data)`
**Rôle :** Fonction principale de validation de la carte
**Vérifications :**
1. Caractères autorisés : 0, 1, espace, N, S, E, W
2. Un et un seul joueur (N/S/E/W)
3. Carte fermée par des murs

#### `static int validate_map_chars(t_datagame *data, int *player_count)`
**Rôle :** Parcourt chaque caractère et vérifie sa validité
**Actions :**
- Compte les joueurs
- Stocke position et direction du joueur
- Remplace le caractère joueur par '0' (devient espace vide)

---

### 📁 map_walls.c

#### `int check_walls(t_datagame *data)`
**Rôle :** Vérifie que tous les espaces vides ('0') sont entourés de murs
**Algorithme :**
```
Pour chaque '0' de la map :
    Vérifier que les 8 cases adjacentes ne sont pas :
    - Hors limites
    - Des espaces
```

#### `int check_neighbor(t_datagame *data, int y, int x)`
**Rôle :** Vérifie les 8 voisins d'une case
**Directions vérifiées :**
```
[-1,-1] [-1,0] [-1,+1]
[ 0,-1]  [0,0]  [0,+1]
[+1,-1] [+1,0] [+1,+1]
```

**Cas d'erreur :**
- Case hors limites → Map ouverte
- Case = espace → Map ouverte

---

### 📁 utils1.c

#### `int ft_isspace(char c)`
**Rôle :** Vérifie si un caractère est un espace blanc
**Caractères acceptés :** espace, tab, \n, \r, \v, \f

#### `int ft_strlen_array(char **arr)`
**Rôle :** Compte le nombre d'éléments dans un tableau de chaînes terminé par NULL

#### `void free_array(char **arr)`
**Rôle :** Libère un tableau de chaînes et toutes les chaînes qu'il contient

#### `long long current_time(void)`
**Rôle :** Retourne le temps actuel en millisecondes
**Utilisation :** Calcul du delta_time pour des mouvements fluides
**Implémentation :**
```c
struct timeval tv;
gettimeofday(&tv, NULL);
return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
```

#### `int is_valid_number(char *str)`
**Rôle :** Vérifie qu'une chaîne contient bien un nombre valide
**Utilisation :** Validation des composantes RGB

---

## Compilation et utilisation

### Prérequis
```bash
# Installer les dépendances (Linux)
sudo apt-get update
sudo apt-get install gcc make xorg libxext-dev libbsd-dev
```

### Compilation
```bash
make          # Compile le projet
make clean    # Supprime les fichiers objets
make fclean   # Supprime tout (objets + exécutable)
make re       # Recompile tout
```

### Utilisation
```bash
./cub3D maps/map.cub
```

### Contrôles
- **W** : Avancer
- **S** : Reculer
- **A** : Aller à gauche
- **D** : Aller à droite
- **←** : Tourner à gauche
- **→** : Tourner à droite
- **ESC** : Quitter

---

## Format du fichier .cub

```
NO ./textures/north_wall.xpm
SO ./textures/south_wall.xpm
EA ./textures/east_wall.xpm
WE ./textures/west_wall.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        1011000001110000000000001
        1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

### Règles :
- **NO/SO/EA/WE** : Chemins vers textures .xpm
- **F** : Couleur du sol (RGB 0-255)
- **C** : Couleur du plafond (RGB 0-255)
- **Map** :
  - `0` : Espace vide
  - `1` : Mur
  - `N/S/E/W` : Position et orientation du joueur
  - ` ` (espace) : Zone vide (hors map)
- La map doit être fermée par des murs

---

## Ressources complémentaires

### Mathématiques
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) - **LA** référence
- [Rotation Matrices](https://en.wikipedia.org/wiki/Rotation_matrix)
- [DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm))

### MinilibX
- [MLX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [MLX Examples](https://github.com/qst0/ft_libgfx)

### Inspirations
- Wolfenstein 3D (1992) - id Software
- DOOM (1993) - id Software

---

## Auteur

Projet réalisé dans le cadre du cursus de l'école 42.

**Bon raycasting! 🎮**
