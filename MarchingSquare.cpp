#include "marchingSquare.h"

CMarchingSquare::CMarchingSquare(std::vector<SommetVoronoi> grilleVoronoi, int nbrLignes, int nbrColonnes):
CModele3DAbstrait(1.0f,(char*)NULL, TYPE_TEXTURE2D, false, false)
{
	nbrColonnes_ = nbrColonnes;
	nbrLignes_ = nbrLignes;
	m_grilleVoronoi = grilleVoronoi;

	creerGrilles(m_grilleVoronoi);
}

CMarchingSquare::~CMarchingSquare(void) {
	glDeleteBuffers(1, &m_sommets_vbo);

}

void CMarchingSquare::creerGrilles(std::vector<SommetVoronoi> grilleVoronoi) {
	int cas = 0;
	for (int x = 0; x < nbrColonnes_-1; x++) {
		for (int y = 0; y < nbrLignes_-1; y++) {

			if (grilleVoronoi[y*nbrColonnes_+ x].matiere) {
				if (grilleVoronoi[y*nbrColonnes_ + x+1].matiere) {
					if (grilleVoronoi[(y+1)*nbrColonnes_ + x].matiere) {
						if (grilleVoronoi[(y+1)*nbrColonnes_ + x+1].matiere) {
							cas = 1;
						}
						else {
							cas = 2;
						}
					}
					else {
						if (grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].matiere) {
							cas = 3;
						}
						else {
							cas = 4;
						}
					}
				}
				else {
					if (grilleVoronoi[(y + 1)*nbrColonnes_ + x].matiere) {
						if (grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].matiere) {
							cas = 5;
						}
						else {
							cas = 6;
						}
					}
					else {
						if (grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].matiere) {
							cas = 7;
						}
						else {
							cas = 8;
						}
					}
				}
			}
			else {
				if (grilleVoronoi[y*nbrColonnes_ + x + 1].matiere) {
					if (grilleVoronoi[(y + 1)*nbrColonnes_ + x].matiere) {
						if (grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].matiere) {
							cas = 9;
						}
						else {
							cas = 10;
						}
					}
					else {
						if (grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].matiere) {
							cas = 11;
						}
						else {
							cas = 12;
						}
					}
				}
				else {
					if (grilleVoronoi[(y + 1)*nbrColonnes_ + x].matiere) {
						if (grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].matiere) {
							cas = 13;
						}
						else {
							cas = 14;
						}
					}
					else {
						if (grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].matiere) {
							cas = 15;
						}
						else {
							cas = 16;
						}
					}
				}
			}
			creerTriangle(cas, x, y);
		}
	}

	glGenBuffers(1, &m_sommets_vbo);

	glBindBuffer(GL_ARRAY_BUFFER, m_sommets_vbo);
	int s_byte_size = m_sommets.size() * sizeof(float);
	glBufferData(GL_ARRAY_BUFFER, s_byte_size, &m_sommets[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (0));//normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (char *)NULL + (3));//positions
}

void CMarchingSquare::dessiner() {
	
	glBindBuffer(GL_ARRAY_BUFFER, m_sommets_vbo);

	if (!m_sommets.empty()) {
		glDrawArrays(GL_TRIANGLES, 0, m_sommets.size());
	}

}

void CMarchingSquare::creerTriangle(int cas, int x, int y) {
	switch (cas) {
	case 1:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_+x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x+1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x+1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y);
		m_sommets.push_back(0.0f);

		break;


	case 2:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		break;

	case 3:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y);
		m_sommets.push_back(0.0f);

		break;

	case 4:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x)/2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x+1].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x+1].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		break;

	case 5:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		break;

	case 6:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_ + x+1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x+1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_ + x+1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x+1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		break;

	case 7:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_+x+1].x)/2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y)/2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x+1].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x+1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x + m_grilleVoronoi[y*nbrColonnes_ + x+1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y + m_grilleVoronoi[y*nbrColonnes_ + x+1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		break;


	case 8:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		break;

	case 9:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x+1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x+1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y);
		m_sommets.push_back(0.0f);

		break;


	case 10:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x + m_grilleVoronoi[y*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x + m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y + m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		break;


	case 11:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y+1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[(y+1)*nbrColonnes_ + x].x+ m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x)/2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		break;

	case 12:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[y*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[y*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x + m_grilleVoronoi[y*nbrColonnes_ + x + 1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y + m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		break;
	case 13:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);

		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x+ m_grilleVoronoi[y*nbrColonnes_ + x + 1].x)/2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y+ m_grilleVoronoi[y*nbrColonnes_ + x + 1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y);
		m_sommets.push_back(0.0f);
		break;

	case 14:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		break;

	case 15:
		// Normale
		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		// Position
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x+1].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[y*nbrColonnes_ + x+1].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y) / 2.0f);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].x);
		m_sommets.push_back(m_grilleVoronoi[(y + 1)*nbrColonnes_ + x+1].y);
		m_sommets.push_back(0.0f);

		m_sommets.push_back(0.0f);
		m_sommets.push_back(0.0f);
		m_sommets.push_back(1.0f);

		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].x + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].x) / 2.0f);
		m_sommets.push_back((m_grilleVoronoi[(y + 1)*nbrColonnes_ + x + 1].y + m_grilleVoronoi[(y + 1)*nbrColonnes_ + x].y) / 2.0f);
		m_sommets.push_back(0.0f);

		break;


	case 16:
		break;
	}

}