#include "Core.Volumetric.SparseOctree.Utils.h"


#include <GL/glew.h>
#include <gl/GLU.h>
#include <SFML/OpenGL.hpp>


namespace  nVolumetric {
namespace  nSparseOctree {
namespace  nUtils {


void
DirectDrawWireFrameCube( float iSize, const  glm::vec3&  iColor )
{
    glBegin( GL_LINES );
        glColor3f( iColor.x, iColor.y, iColor.z );
        glVertex3f( 0.f,    0.f,    0.f     );
        glVertex3f( iSize,  0.f,    0.f     );

        glVertex3f( 0.f,    0.f,    0.f     );
        glVertex3f( 0.f,    iSize,  0.f     );

        glVertex3f( 0.f,    0.f,    0.f     );
        glVertex3f( 0.f,    0.f,    iSize   );

        glVertex3f( iSize,  iSize,  iSize   );
        glVertex3f( 0.f,    iSize,  iSize   );

        glVertex3f( iSize,  iSize,  iSize   );
        glVertex3f( iSize,  0.f,    iSize   );

        glVertex3f( iSize,  iSize,  iSize   );
        glVertex3f( iSize,  iSize,  0.f     );

        glVertex3f( 0.f,    iSize,  0.f     );
        glVertex3f( iSize,  iSize,  0.f     );

        glVertex3f( 0.f,    iSize,  0.f     );
        glVertex3f( 0.f,    iSize,  iSize   );

        glVertex3f( iSize,  0.f,    0.f     );
        glVertex3f( iSize,  iSize,  0.f     );

        glVertex3f( iSize,  0.f,    0.f     );
        glVertex3f( iSize,  0.f,    iSize   );

        glVertex3f( 0.f,    0.f,    iSize   );
        glVertex3f( iSize,  0.f,    iSize   );

        glVertex3f( 0.f,    0.f,    iSize   );
        glVertex3f( 0.f,    iSize,  iSize   );
    glEnd();
}


} // namespace  nUtils
} // namespace  nSparseOctree
} // namespace  nVolumetric

