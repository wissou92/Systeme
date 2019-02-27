#ifndef H_GL_FONCTION
#define H_GL_FONCTION

// Affiche le type du fichier indiqué par le PATH
int aff_type(const char* pathname);

// Affiche les permissions du fichier indiqué par le PATH
int aff_permission(const char* pathname);

// Affiche le propriétaire du fichier indiqué par le PATH
int aff_proprietaire(char const* pathname);

// Affiche la taille du fichier indiqué par le PATH
int aff_taille(const char* pathname);

#endif
