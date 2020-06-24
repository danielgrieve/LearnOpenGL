#include <iostream>
#include <GLFW/glfw3.h>

void process_input(GLFWwindow *window);

int main() {
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    GLFWwindow *window = glfwCreateWindow(800, 480, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    while (!glfwWindowShouldClose(window)) {
        process_input(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

    return 0;
}

void process_input(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}