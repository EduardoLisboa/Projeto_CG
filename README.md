# Projeto de Computação Gráfica

Alunos:
* Eduardo Antônio de Lucena Lisboa
* Jonathas Patrick Hermenegildo de Azevedo

### Para compilar o programa é necessária uma biblioteca chamada ***freeglut*** disponível [aqui](https://www.transmissionzero.co.uk/software/freeglut-devel/)
A versão utilizada foi a MinGW e para compilar o programa é necessário utilizar o seguinte comando no terminal do Windows:
~~~
gcc main.c -o main.exe -I"C:\Endereço\Para\Pasta\include" -L"C:\Endereço\Para\Pasta\lib" -lfreeglut -lopengl32 -lglu32
~~~
Essas pastas "include" e "lib" são as que foram baixadas no link acima e as pastas "objects" e "textures" precisam estar na mesma pasta do arquivo __*main.c*__

### Implementações
- [X] Quarto
- [X] Iluminação básica
- [X] Movimentação
- [X] Câmera em primeira pessoa
- [X] Movimentação da porta principal
- [X] Movimentação da porta secundária
- [X] Movimentação das janelas
- [ ] Ventilador com movimento perpétuo
- [ ] Luminária spot
- [ ] Quadro de Van Gogh
- [ ] Texturas em pelo menos 5 objetos

### Renderização de um quarto com:
* 3 camas (um beliche e uma cama)
* Armário
* Portas
* Mesa
* Cadeira
* Computador
* Teclado
* Dois monitores
* Mouse
* Prateleira
* Luminária
* Ar condicionado

### Referências
* <https://stackoverflow.com/questions/41858408/how-to-load-texture-opengl>
* <http://www.opengl-tutorial.org/beginners-tutorials/tutorial-5-a-textured-cube/>
* <https://computergraphics.stackexchange.com/questions/4310/how-to-translate-object-to-origin>
* <https://community.khronos.org/t/opengl-creating-a-command-to-open-a-door/65403/3>
* <http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-17-quaternions/#euler-angles>
* <https://www.youtube.com/watch?v=ZXjL7EqpSw8&ab_channel=gamedevlog>
* <https://github.com/totex/Learn-OpenGL-in-python>
* <https://www.labri.fr/perso/nrougier/python-opengl/>
* <https://docs.microsoft.com/en-us/windows/win32/opengl/opengl>
* <http://docs.gl/>
* <https://docs.microsoft.com/en-us/windows/win32/opengl/opengl>
* <https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glTexParameter.xhtml>
* <https://www.khronos.org/registry/OpenGL-Refpages/gl4/html/glBindTexture.xhtml>
