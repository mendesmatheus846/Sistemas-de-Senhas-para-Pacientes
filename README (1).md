# Sistema de Senhas para Pacientes

Projeto em linguagem C para registrar pacientes, classificar prioridades, emitir senhas e organizar a fila de atendimento.

## Objetivo

O programa simula o atendimento de uma clínica: o atendente cadastra o paciente, o sistema descobre sozinho a categoria dele, gera uma senha e depois chama os pacientes na ordem certa, mostrando tudo num painel.

## O que o programa faz

- **Registro:** pergunta gênero, idade, gestante e lactante (só se for mulher), necessidade especial e obesidade.
- **Classificação automática** em três categorias:
  - **U (Urgente):** idade acima de 80 anos.
  - **P (Preferencial):** gestante, lactante, necessidade especial, obesidade, mulher com 60 anos ou mais, ou homem com 65 anos ou mais.
  - **N (Normal):** quem não se encaixa em nenhuma das anteriores.
- **Senhas sequenciais** por categoria (U001, U002, P001, N001...).
- **Chamada:** urgentes primeiro, depois preferenciais, depois normais. Dentro de cada categoria vale a ordem em que a senha foi emitida.
  Exemplo: se as senhas emitidas foram N001, P001, N002, U001 e P002, a ordem de chamada é U001, P001, P002, N001, N002.
- **Finalizar atendimento:** libera para chamar o próximo.
- **Painel:** mostra a senha atual e sua categoria, as próximas senhas e quantas pessoas esperam em cada categoria.

O programa também não aceita idade negativa, opção de menu que não existe, gênero diferente de F ou M, letras no lugar de números, e avisa quando tentam chamar com as filas vazias.

## Como compilar e executar

```
gcc senhas.c -o senhas
./senhas
```

## Funções do código

- `main()` – só mostra o menu e chama as outras funções
- `exibirMenu()` – imprime as opções
- `lerNumero()` – lê um número e repete até ser válido
- `lerGenero()` – lê o gênero e repete até ser F ou M
- `registrarPaciente()` – pega os dados do paciente
- `classificar()` – devolve U, P ou N
- `emitirSenha()` – cria a senha e coloca na fila da categoria
- `chamarProxima()` – chama a próxima senha seguindo a prioridade
- `finalizarAtendimento()` – termina o atendimento atual
- `exibirPainel()` – mostra o painel

## Como funcionam as filas

Cada categoria tem um vetor e duas variáveis: `ini` (próximo a ser chamado) e `fim` (próxima posição livre). Para emitir, guarda em `fila[fim]` e faz `fim++`. Para chamar, lê `fila[ini]` e faz `ini++`. A quantidade de gente esperando é `fim - ini`.

## Exemplo de uso

Registrando uma mulher de 85 anos e depois olhando o painel:

```
Opcao: 1
Genero (F/M): F
Idade: 85
Gestante (1-sim, 0-nao): 0
Lactante (1-sim, 0-nao): 0
Necessidade especial (1-sim, 0-nao): 0
Obesidade (1-sim, 0-nao): 0
Categoria: U
Senha emitida: U001

Opcao: 4

===== PAINEL =====
Senha atual: nenhuma
Proximas: U001
Esperando - U: 1 | P: 0 | N: 0
```

Chamando a próxima senha:

```
Opcao: 2
Chamando a senha U001
```
