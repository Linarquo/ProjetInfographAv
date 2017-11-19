#pragma once


#include "Cst.h"
#include "Modele3DAbstrait.h"
#include "Lumiere.h"
#include  <GL/glew.h> 
#include <vector>
#include "Var.h"



class CMarchingSquare:CModele3DAbstrait{
public :
	CMarchingSquare(std::vector<SommetVoronoi> grilleVoronoi, int nbrLignes, int nbrColonnes);

	~CMarchingSquare(void);

	void dessiner();

private :
	std::vector<SommetVoronoi> m_grilleVoronoi;
	std::vector<float> m_sommets;
	int nbrLignes_;
	int nbrColonnes_;
	
	/// ID du VBO pour les sommets
	GLuint			 m_sommets_vbo;
	/// ID du IBO pour les quads
	//GLuint			 m_quads_ibo;
	/// ID du VAO pour les triangles
	//GLuint			 m_tri_vao;
	/// Nombre de floats à lire lors de l'affichage
	//GLint			 m_size;

	void creerGrilles(std::vector<SommetVoronoi> grilleVoronoi);
	void CMarchingSquare::creerTriangle(int cas, int x, int y);
};