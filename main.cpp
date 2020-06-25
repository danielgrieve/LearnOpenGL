#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow*, int, int);
void process_input(GLFWwindow*);

const char* vertex_shader_source = "#version 330 core\n"
                                   "layout (location = 0) in vec3 a_pos;\n"
                                   "void main() {\n"
                                   "    gl_Position = vec4(a_pos.x, a_pos.y, a_pos.z, 1.0);\n"
                                   "}\0";

const char* orange_fragment_shader_source = "#version 330 core\n"
                                            "out vec4 FragColor;\n"
                                            "void main() {\n"
                                            "    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                            "}\0";

const char* yellow_fragment_shader_source = "#version 330 core\n"
                                            "out vec4 FragColor;\n"
                                            "void main() {\n"
                                            "    FragColor = vec4(1.0f, 1.0f, 0.0f, 1.0f);\n"
                                            "}\0";

int main() {
    // GL setup
    if (!glfwInit()) {
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);
    if (window == NULL) {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return EXIT_FAILURE;
    }

    // Compile and link shaders
    unsigned int vertex_shader;
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
    glCompileShader(vertex_shader);

    int success;
    char info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    unsigned int orange_fragment_shader;
    orange_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(orange_fragment_shader, 1, &orange_fragment_shader_source, NULL);
    glCompileShader(orange_fragment_shader);
    glGetShaderiv(orange_fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(orange_fragment_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    unsigned int yellow_fragment_shader;
    yellow_fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(yellow_fragment_shader, 1, &yellow_fragment_shader_source, NULL);
    glCompileShader(yellow_fragment_shader);
    glGetShaderiv(yellow_fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(yellow_fragment_shader, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << info_log << std::endl;
    }

    unsigned int orange_shader_program;
    orange_shader_program = glCreateProgram();
    glAttachShader(orange_shader_program, vertex_shader);
    glAttachShader(orange_shader_program, orange_fragment_shader);
    glLinkProgram(orange_shader_program);
    glGetProgramiv(orange_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(orange_shader_program, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    unsigned int yellow_shader_program;
    yellow_shader_program = glCreateProgram();
    glAttachShader(yellow_shader_program, vertex_shader);
    glAttachShader(yellow_shader_program, yellow_fragment_shader);
    glLinkProgram(yellow_shader_program);
    glGetProgramiv(yellow_shader_program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(yellow_shader_program, 512, NULL, info_log);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(orange_fragment_shader);
    glDeleteShader(yellow_fragment_shader);

    // Set up vertex data and buffers
//    const float vertices[] = {
//             0.5f,  0.5f, 0.0f, // top right
//             0.5f, -0.5f, 0.0f, // bottom right
//            -0.5f, -0.5f, 0.0f, // bottom left
//            -0.5f,  0.5f, 0.0f  // top left
//    };
//    const unsigned int indices[] = {
//            0, 1, 3, // first triangle
//            1, 2, 3  // second triangle
//    };

    const float first_triangle[] = {
            -0.5f, 0.75f, 0.0f, // top
            -0.85f, 0.0f, 0.0f, // left
            -0.15f, 0.0f, 0.0f  // right
    };

    const float second_triangle[] = {
             0.5f,   0.00f, 0.0f, // top
             0.15f, -0.75f, 0.0f, // left
             0.85f, -0.75f, 0.0f  // right
    };

    unsigned int VAOs[2], VBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);

    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(first_triangle), first_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(second_triangle), second_triangle, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        process_input(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(orange_shader_program);
        glBindVertexArray(VAOs[0]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glUseProgram(yellow_shader_program);
        glBindVertexArray(VAOs[1]);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(orange_shader_program);
    glDeleteProgram(yellow_shader_program);

    glfwTerminate();
    return EXIT_SUCCESS;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void process_input(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}