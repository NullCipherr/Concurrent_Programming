# Semáforo

![Semáforo](https://img.shields.io/badge/Semáforo-C-green)
![Licença](https://img.shields.io/badge/Licença-MIT-blue)
![Status](https://img.shields.io/badge/Status-Em%20Desenvolvimento-yellow)

## Índice

- [Introdução](#introdução)
- [Pré-requisitos](#pré-requisitos)
- [Instalação](#instalação)
- [Uso](#uso)
- [Exemplo de Código](#exemplo-de-código)
- [Contribuição](#contribuição)
- [Licença](#licença)
- [Contato](#contato)

## Introdução

Este repositório contém um exemplo detalhado de como usar semáforos em C para controlar o acesso a recursos compartilhados em programas multithreaded. Semáforos são uma ferramenta de sincronização essencial para evitar condições de corrida e garantir que apenas um thread ou processo acesse um recurso crítico por vez.

## Pré-requisitos

Antes de começar, certifique-se de ter os seguintes pré-requisitos instalados:

- **GCC (GNU Compiler Collection)**: Compilador C para compilar o código.
- **POSIX Threads (pthread)**: Biblioteca para suporte a threads em C.
- **Semaphore**: Biblioteca para suporte a semáforos em C.

## Instalação

1. **Clone o repositório**:

   ```sh
   git clone https://github.com/NullCipherr/Concurrent_Programming.git
   cd Concurrent_Programming
   ```

2. **Compile o código**:

   ```sh
   gcc -pthread ./Semaphores/Basic_Semaphore.c -o Basic_Semaphore
   ```

## Uso

Para executar o programa, use o seguinte comando:

```sh
./Basic_Semaphore
```

## Exemplo de Código

Aqui está um exemplo básico de como usar semáforos em C com a biblioteca POSIX (`pthread`):

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_THREADS 4

// Definindo um semáforo
sem_t semaphore;

void *threadWork(void *arg)
{
    // Espera pelo semáforo
    sem_wait(&semaphore);

    // Seção crítica
    printf("Thread %d está na seção crítica\n", *(int *)arg);

    // Simula algum trabalho : 1 segundo
    sleep(1);

    // Libera o semáforo
    sem_post(&semaphore);

    return NULL;
}

int main()
{
    pthread_t threads[NUM_THREADS];
    int thread_id[NUM_THREADS] = {1, 2, 3, 4};

    printf("Iniciando o programa...\n");

    // Inicializa o semáforo com o valor 1 (Semáforo binário) -> Mutex
    sem_init(&semaphore, 0, 1);

    // Cria as threads
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_create(&threads[i], NULL, threadWork, &thread_id[i]);
    }

    // Espera as threads terminarem
    for (int i = 0; i < NUM_THREADS; i++)
    {
        pthread_join(threads[i], NULL);
    }

    // Destrói o semáforo
    sem_destroy(&semaphore);

    printf("Finalizando o programa...\n");

    return 0;
}
```

## Contribuição

Contribuições são bem-vindas! Se você encontrar um bug ou tiver uma sugestão de melhoria, por favor, abra uma issue ou envie um pull request.

1. **Fork o repositório**
2. **Crie uma branch para sua feature** (`git checkout -b feature/nova-feature`)
3. **Commit suas mudanças** (`git commit -m 'Adiciona nova feature'`)
4. **Push para a branch** (`git push origin feature/nova-feature`)
5. **Abra um Pull Request**

## Licença

Este projeto está licenciado sob a Licença MIT - veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## Contato

Se você tiver alguma dúvida ou sugestão, sinta-se à vontade para entrar em contato:

- **Email**: seu-email@example.com
- **LinkedIn**: [Seu Perfil no LinkedIn](https://www.linkedin.com/in/seu-perfil/)
- **Twitter**: [@seu-usuario](https://twitter.com/seu-usuario)

---

Espero que este README.md seja útil para você! Se precisar de mais alguma coisa, estou à disposição.
