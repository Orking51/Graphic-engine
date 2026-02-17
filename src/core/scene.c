#include "scene.h"
#include <glad/glad.h>                                  
#include <GLFW/glfw3.h>  

void scene(){

    Object3D* objects[32];
    int objectCount = 0;

    objects[objectCount++] = create_pyramid(3.0, 3.0);

    while (!window_should_close())
    {
        renderer_clear();   //éfface l'image actuelle (nécéssaire pour que les img ne s'empille pas et créer des trainé / comportement non déterministe)
                                  //déssiner la nouvelle image. (appel des shader, bind VAO/VBO ...) 
        renderer_draw(objects, objectCount);

        window_swap_buffers();  //Afficher ce "dessin", càd l'image actuelle. 
                                //Pour se faire OpenGl utilise le double buffering. En gros on dessine dans un back buffer et on affiche depuis un front buffer.
                                //Et pour des raisons que je ne comprends pas encore, en plus d'afficher l'image ça permet d'éviter le flickering.
        
        window_poll_events();   //Traite les event (sinon notre programme est mort).
                                //OpenGl ne gère pas les event, c'est le rôle de Glfw (ou SDL)
    }

    renderer_shutdown(objects, objectCount);    //libère les ressources GPU: shader, VAO/VBO, textures ...

}