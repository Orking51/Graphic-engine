#include <stdio.h>
#include "core/window.h"      //fenêtre et event (OpenGl ne sais pas créer une fenêtre tout seul, il a besoin de Glfw (ou SDL))
#include "core/renderer.h"    //moteur de rendu. Initialise OpenGl, dessine, néttoye. En gros utilise OpenGl
#include "core/configuration.h"
#include "core/scene.h"

int main(void)
{
    WindowConfig winCfg;
    window_config_defaults(&winCfg);

    if (!window_init(winCfg.width, winCfg.height, winCfg.title)) //Créer une fenêtre et un contexte OpenGl valide (Nécéssaire pour faire tourner OpenGl) | coté: Système/OS/fenêtre
        return -1;

    renderer_init(winCfg);    //Initialise OpenGL (chargement de glad/glew...) = Configuration de base | coté: GPU/OpenGl
    scene();

    window_shutdown();      //Ferme correctement la fenêtre, le contexte OpenGl, et la lib système (ici Glfw)

    return 0;
}