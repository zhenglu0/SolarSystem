[1mdiff --git a/draw.h b/draw.h[m
[1mindex ce0b185..d3f7b53 100644[m
[1m--- a/draw.h[m
[1m+++ b/draw.h[m
[36m@@ -6,51 +6,51 @@[m
 [m
 [m
 void gltDrawSphere(GLfloat fRadius, GLint iSlices, GLint iStacks)[m
[32m+[m[32m{[m[41m[m
[32m+[m[32m    GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;[m[41m[m
[32m+[m[32m    GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;[m[41m[m
[32m+[m[32m    GLfloat ds = 1.0f / (GLfloat) iSlices;[m[41m[m
[32m+[m[32m    GLfloat dt = 1.0f / (GLfloat) iStacks;[m[41m[m
[32m+[m[32m    GLfloat t = 1.0f;[m[41m    [m
[32m+[m[32m    GLfloat s = 0.0f;[m[41m[m
[32m+[m[32m    GLint i, j;[m[41m    [m
[32m+[m[41m[m
[32m+[m[32m    for (i = 0; i < iStacks; i++)[m[41m [m
     {[m
[31m-        GLfloat drho = (GLfloat)(3.141592653589) / (GLfloat) iStacks;[m
[31m-        GLfloat dtheta = 2.0f * (GLfloat)(3.141592653589) / (GLfloat) iSlices;[m
[31m-	GLfloat ds = 1.0f / (GLfloat) iSlices;[m
[31m-	GLfloat dt = 1.0f / (GLfloat) iStacks;[m
[31m-	GLfloat t = 1.0f;	[m
[31m-	GLfloat s = 0.0f;[m
[31m-        GLint i, j;    [m
[31m-[m
[31m-	for (i = 0; i < iStacks; i++) [m
[31m-		{[m
[31m-		GLfloat rho = (GLfloat)i * drho;[m
[31m-		GLfloat srho = (GLfloat)(sin(rho));[m
[31m-		GLfloat crho = (GLfloat)(cos(rho));[m
[31m-		GLfloat srhodrho = (GLfloat)(sin(rho + drho));[m
[31m-		GLfloat crhodrho = (GLfloat)(cos(rho + drho));[m
[31m-[m
[31m-		glBegin(GL_TRIANGLE_STRIP);[m
[32m+[m[32m        GLfloat rho = (GLfloat)i * drho;[m[41m[m
[32m+[m[32m        GLfloat srho = (GLfloat)(sin(rho));[m[41m[m
[32m+[m[32m        GLfloat crho = (GLfloat)(cos(rho));[m[41m[m
[32m+[m[32m        GLfloat srhodrho = (GLfloat)(sin(rho + drho));[m[41m[m
[32m+[m[32m        GLfloat crhodrho = (GLfloat)(cos(rho + drho));[m[41m[m
[32m+[m[41m[m
[32m+[m[32m        glBegin(GL_TRIANGLE_STRIP);[m[41m[m
                 s = 0.0f;[m
[31m-		for ( j = 0; j <= iSlices; j++) [m
[31m-			{[m
[31m-			GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;[m
[31m-			GLfloat stheta = (GLfloat)(-sin(theta));[m
[31m-			GLfloat ctheta = (GLfloat)(cos(theta));[m
[31m-[m
[31m-			GLfloat x = stheta * srho;[m
[31m-			GLfloat y = ctheta * srho;[m
[31m-			GLfloat z = crho;[m
[32m+[m[32m        for ( j = 0; j <= iSlices; j++)[m[41m [m
[32m+[m[32m        {[m[41m[m
[32m+[m[32m            GLfloat theta = (j == iSlices) ? 0.0f : j * dtheta;[m[41m[m
[32m+[m[32m            GLfloat stheta = (GLfloat)(-sin(theta));[m[41m[m
[32m+[m[32m            GLfloat ctheta = (GLfloat)(cos(theta));[m[41m[m
[32m+[m[41m[m
[32m+[m[32m            GLfloat x = stheta * srho;[m[41m[m
[32m+[m[32m            GLfloat y = ctheta * srho;[m[41m[m
[32m+[m[32m            GLfloat z = crho;[m[41m[m
             [m
                         glTexCoord2f(s, t);[m
                         glNormal3f(x, y, z);[m
                         glVertex3f(x * fRadius, y * fRadius, z * fRadius);[m
 [m
                         x = stheta * srhodrho;[m
[31m-			y = ctheta * srhodrho;[m
[31m-			z = crhodrho;[m
[31m-			glTexCoord2f(s, t - dt);[m
[32m+[m[32m            y = ctheta * srhodrho;[m[41m[m
[32m+[m[32m            z = crhodrho;[m[41m[m
[32m+[m[32m            glTexCoord2f(s, t - dt);[m[41m[m
                         s += ds;[m
                         glNormal3f(x, y, z);[m
                         glVertex3f(x * fRadius, y * fRadius, z * fRadius);[m
[31m-                        }[m
[32m+[m[32m        }[m[41m[m
                glEnd();[m
 [m
                t -= dt;[m
[31m-               }[m
[31m-    }[m
[32m+[m[32m        }[m[41m[m
[32m+[m[32m}[m[41m[m
 [m
[31m-#endif[m
\ No newline at end of file[m
[32m+[m[32m#endif[m[41m[m
[1mdiff --git a/mf.h b/mf.h[m
[1mindex 36c8738..daa14ee 100644[m
[1m--- a/mf.h[m
[1m+++ b/mf.h[m
[36m@@ -9,26 +9,23 @@[m
 [m
 void mf(TEXTUREIMAGE textureImg, GLuint * texName)[m
 {[m
[31m-	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);[m
[32m+[m[32m    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);[m[41m[m
 [m
[31m-	glGenTextures(1,texName);[m
[32m+[m[32m    glGenTextures(1,texName);[m[41m[m
 [m
[31m-        glBindTexture(GL_TEXTURE_2D , *texName);[m
[32m+[m[32m    glBindTexture(GL_TEXTURE_2D , *texName);[m[41m[m
 [m
[31m-        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);[m
[32m+[m[32m    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);[m[41m[m
 [m
[31m-	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);[m
[32m+[m[32m    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);[m[41m[m
 [m
[31m-        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);[m
[32m+[m[32m    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);[m[41m[m
 [m
[31m-        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);[m
[32m+[m[32m    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);[m[41m[m
 [m
[31m-        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImg.imgWidth,textureImg.imgHeight, 0,[m
[32m+[m[32m    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureImg.imgWidth,textureImg.imgHeight, 0,[m[41m[m
 [m
[31m-         GL_RGB, GL_UNSIGNED_BYTE, textureImg.data);[m
[31m-	[m
[31m-[m
[31m-   [m
[32m+[m[32m    GL_RGB, GL_UNSIGNED_BYTE, textureImg.data);[m[41m[m
 }[m
 [m
[31m-#endif[m
\ No newline at end of file[m
[32m+[m[32m#endif[m[41m[m
