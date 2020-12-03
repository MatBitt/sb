Nome: Mateus de Moura Ramos Bittencourt
Matricula: 160079284

Trabalho 2

Para executar o programa, deve-se entrar na pasta trabalho2 pelo terminal.
Em seguida, insere-se as seguintes linhas de comando:

g++ main.cpp -Wall
./a.out [path_to_file].asm

Onde [path_to_file] é o caminho para o arquivo partindo da pasta trabalho2.

Após isso, o arquivo .s é gerado, para executá-lo, insere-se as seguintes linhas de comando:

nasm -f elf -o [path_to_file].o [path_to_file].s
ld -o [path_to_file] [path_to_file].o
./[path_to_file]

Novamente, path_to_file é o diretório do arquivo.