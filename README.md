# Projeto de Computação Gráfica

### Para compilar o programa é necessária uma biblioteca chamada ***freeglut*** disponível [aqui](https://www.transmissionzero.co.uk/software/freeglut-devel/)
A versão utilizada foi a MinGW e para compilar o programa é necessário utilizar o seguinte comando:
~~~
gcc main.c -o main.exe -I"C:/Endereço/Para/Pasta/include" -L"C:/Endereço/Para/Pasta/lib" -lfreeglut -lopengl32 -lglu32
~~~
Essas pastas "include" e "lib" são as que foram baixadas no link acima.

### Implementações
- [X] Quarto
- [X] Iluminação básica
- [X] Movimentação
- [X] Câmera em primeira pessoa
- [X] Movimentação da porta principal
- [X] Movimentação da porta secundária
- [X] Movimentação das janelas
- [ ] Ventilador com movimento perpétuo
- [ ] Luminário spot
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
