/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   roadmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rickymercury <rickymercury@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 11:44:43 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/08/28 21:50:40 by rickymercur      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

O projeto Fract-ol convida-nos a entrar num universo onde são criadas representações
visuais de padrões infinitamente complexos. Neste projeto, o objetivo principal é 
representar graficamente fractais (figuras geométricas que se repetem a diferentes
escalas e que exibem uma beleza hipnotizante que emerge da pura lógica matemática).

Através da biblioteca gráfica MiniLibX, o programa renderiza imagens matematicamente
determinadas e permite ao utilizador explorar estes padrões com interações em tempo
real, como o zoom e o deslocamento da imagem. Além disso, permite alternar entre 
diferentes tipos de fractais (como Mandelbrot, Julia, Burning Ship ou Phoenix), ajustar
a resolução dos cálculos e modificar o esquema de cores.

Mas para realmente compreender o que está por detrás daquilo que vemos no ecrã, é necessário
entender dois conceitos centrais: fractais e números complexos.

> O Que São Fractais?
 
  Fractais são estruturas geométricas que apresentam auto-semelhança — ou seja, os seus
  padrões repetem-se em diferentes escalas. Isto significa que, se dermos zoom num fractal,
  veremos uma estrutura que se parece com a imagem inicial, e se continuarmos a ampliar,
  encontraremos mais padrões semelhantes, num ciclo aparentemente infinito. Esta propriedade 
  dá origem a imagens visualmente ricas e complexas, mesmo que definidas por fórmulas matemáticas 
  extremamente simples.

  Fractais são amplamente estudados em matemática, mas também ocorrem frequentemente na natureza: 
  na forma de flocos de neve, na ramificação de árvores, nas margens irregulares das nuvens ou dos
  rios, e até mesmo nos pulmões humanos.

> O Papel dos Números Complexos

  Para criar e explorar os fractais como os de Mandelbrot e Julia, entramos no domínio dos números
  complexos. Um número complexo é composto por uma parte real e uma parte imaginária, e é normalmente
  representado como:

  z = a + bi

  Onde: - a é a parte real,
        - b é a parte imaginária,
        - i é a unidade imaginária, tal que i^2 = -1

  Num sistema de coordenadas bidimensional, os números complexos podem ser visualizados como pontos 
  num plano (plano complexo), onde o eixo horizontal representa a parte real e o eixo vertical 
  representa a parte imaginária.

  A razão pela qual os números complexos são cruciais para o Fract-ol é que os algoritmos que criam os
  fractais funcionam ao iterar funções matemáticas no plano complexo.

  Neste caso, tanto z como c são números complexos. O comportamento desta sequência determina se o ponto 
  c pertence ao conjunto ou não. Se a sequência diverge (cresce infinitamente), o ponto é excluído; 
  Se permanece limitada, o ponto pertence ao fractal.


> Por Que Precisamos Usar Números Complexos?

  Fractais como o Mandelbrot e a Julia não podem ser expressos unicamente com números reais. As operações
  de iteração, envolvendo somas e multiplicações entre os valores com as componentes reais e imaginárias, apenas 
  fazem sentido no conjunto dos números complexos.

  Os números reais têm apenas uma dimensão: uma linha, não um plano. 
  O ecrã é em duas dimensões (x e y), mas se a variável do sistema que vamos iterarfor real, a dinâmica ocorrerá
  em apenas uma dimensão.
  Assim, se trabalhassemos com números reais, para desenhar/pintar uma imagem (2D), precisaríamos de um “segundo eixo” artificial.
  
  O número complexo z tem duas componentes (a e b) e ela é em duas dimensões de raiz e as suas operações (especialmente o produto) têm 
  um significado geométrico (rotação + escala) que os reais não têm — e isto é exatamente o que dá vida às formas fractais.

  Além disso, a geometria do plano complexo permite uma forma elegante de representar padrões simétricos e 
  bidimensionais — o que seria impossível ou extremamente limitado com apenas uma dimensão (números reais). 
  A beleza e complexidade dos fractais vêm precisamente desta interação rica entre as componentes reais e 
  imaginárias de cada ponto.

  Usando os números complexos, podemos transformar a posição de cada pixel da imagem num ponto do plano 
  complexo, aplicar a função iterativa sobre ele, e depois decidir a cor desse pixel com base no número de
  iterações necessárias até que o ponto "escape" ou atinja um certo limite.



1 - Função principal - main

int	main(int ac, char **av)
{
	t_fractol	f;

	init_defaults(&f);    (1.1)
	check_input(&f, ac, av);  (1.2)
	init_fractol(&f);  (1.3)
	ft_putstr("Program launched, press h for help\n");
	render_fractal(&f);  (1.4)
	mlx_key_hook(f.win, (int (*)())(void *)handle_key, &f);  (1.5)
	mlx_mouse_hook(f.win, (int (*)())(void *)handle_mouse_key, &f);  (1.6)
	mlx_hook(f.win, 17, 0, (int (*)())(void *)handle_close, &f);   (1.7)
	mlx_loop(f.mlx);   (1.8)
    return (0);
}


A função main é o ponto de entrada do programa. É aqui que a execução começa. O programa espera argumentos
via linha de comandos (como "mandelbrot" ou "julia 0.285 0.01"), que são recebidos como:

ac → argument count (número de argumentos),

av → argument vector (array de strings com os argumentos).

Primeiro: Com a função init_defaults(), inicializamos todos os campos da struct t_fractol com os valores 
          default, de modo a garantir que a struct começa num estado limpo, evitando comportamento indenifido ao
          utilizar ponteiros não inicializados ou váriaveis com "lixo".

Segundo: Com a função check_input() validamos os argumentos fornecidos pelo utilizador, definimos o tipo de fractal
         (f->type) e, se necessário, atribui os parâmetros do fractal Julia ou Phoenix.
         Caso os argumentos estejam incorretos, a função exit_fractol() é chamada e termina o programa com uma mensagem
         de erro.
        
Terceiro: Com a função init_fractol() iniciamos o sistema gráfico da MiniLibX (mlx_init). Criamos uma janela com tamanho
          WIDTH x HEIGHT (mlx_new_window) e definimos o número máximo de iterações iniciais (f->c_max_iter = MAX_ITER), 
          o zoom inicial (f->zoom = 1) e criamos a tabela de cores (update_color_table()).
          A função init_fractol() prepara o ambiente gráfico para renderizar os fractais.

Quarto: Com a função render_fractal(), desenhamos o fractal no ecrã com base no tipo do fractal (ft->type) e com base nos 
        parâmetros (zoom, offset, iterações, etc).
        A função: - Cria uma imagem (init_image),
                  - Percorre todos os pixels da janela,
                  - Converte as coordenadas (x, y) → número complexo (re, im),
                  - Aplica a fórmula do fractal correspondente,
                  - Calcula o número de iterações até ocorrer uma divergência,
                  - Usa o color_table para atribuir a cor ao pixel.

Quinto: Com a função mlx_key_hook() ligamos a função handle_key() ao evento do teclado.
        Sempre que o utilizador carregar numa tecla, a função handle_key é chamada.

Sexto: Com a função mlx_mouse_hook() ligamos a função handle_mouse_key aos eventos do rato (scroll).
       A função utiliza as coordenados do cursor (x, y) para aplicar o zoom relativo ao ponto onde o
       rato está.

Sétimo: COm a função mlx_hook() ligamos a função handle_close ao evento do fecho da janela.
        QUando o utilizador tenta fechar manualmente a janela, o handle_close() é chamada, que por sua vez
        chamada a função exit_fractol(), o que vai garantir a libertação da memória e o encerramento seguro.

Oitavo: A função mlx_loop() é o loop principal do programa, que pertence à MiniLibx.
        A função espera pelos eventos (teclas, rato, fecho), atualiza a janela conforme necessário e garante
        que o programa fica ativo até o utilizador decidir sair.
        Enquanto o utilizador interage, a aplicação continua a responder graças a este loop.



1.1 - init_defaults()

void	init_defaults(t_fractol *f)
{
	f->mlx = NULL;
	f->win = NULL;
	f->img.img = NULL;
	f->type = NULL;
	f->c_max_iter = 0;
	f->color_mode = 0;
	f->color_table = NULL;
	f->zoom = 1.0;
	f->offset_x = 0;
	f->offset_y = 0;
	f->julia_re = 0;
	f->julia_im = 0;
	f->pv.p.re = 0;
	f->pv.p.im = 0;
	f->pv.c.re = 0;
	f->pv.c.im = 0;
}


A função init_defaults() garante que a struct t_fractol (que armazena todo o estado necessário para criar e
visualizar os fractais) seja inicializada com valores seguros, ou seja, esta função inicializa todos os campos
da struct t_fractol com os valores padrão, evitando comportamentos indesejados causados por valores "lixo" na 
memória e prepara a struct para ser utilizada em funções posteriores (como o parsing, inicialização gráfica, 
renderização, etc).

f->mlx = NULL;

> mlx: é o ponteiro devoldido pela função mlx_init(). Ele é inicializado com NULL para saber se a MLX foi 
       corretamente iniciada.
       Enquanto a janela não for criada, o ponteiro não pode apontar para nada.
       Inicializar com NULL ajuda a garantir que não se chama funções como a mlx_destroy_window() com um
       ponteiro inválido.
     
f->win = NULL;

> win: é o ponteiro para a janela criada com a função mlx_new_window(). Inicializamos com NULL porque ainda
       não foi criada nenhuma janela gráfica com a MiniLibX. Mais tarde, quando chamamos a função 
       mlx_new_window(), o ponteiro f->win passa a apontar para a janela criada.
       O ponteiro win é essencial para desenhar a imagem do fractal.

f->img.img = NULL;

> img.img: é a imagem que será criada com a função mlx_new_image(). É o ponteiro devolvido pela função
           mlx_new_image(), ou seja, é a imagem que vai ser desenhada na memória.
           Representa o ponteiro devolvido pela função mlx_new_image(), que representa uma imagem na
           memória onde se desenha pixel a pixel.
           Inicialmente não foi criada nenhuma imagem -> NULL.
           Primeiramente, imagem será desenhada com a função mlx_new_image() na memória:
           
           f->img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
           
           Depois, essa imagem será modificada pixel a pixel (via addr, put_pixel(), etc) e finalmente
           desenhada na janela com: 

           mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);

NOTA: outros campos da struct t_img como addr, bits_per_pixel, etc, são configurados depois na função
      init_image() e não precisam de ser inicializados aqui.
      
f->type = NULL;

> Armazena o nome do fractal a ser desenhado e define o tipo de fractal definido a partir dos argumentos 
  escolhidos pelo utilizador. 
  Começa com NULL, até ser validado na função check_input(), pois ainda não foi definido nenhum
  fractal a ele. 
  Após o parsing dos argumentos (check_input()) esta variável é utilizada para selecionar qual função de 
  desenho chamar.

f->c_max_iter = 0;

> Representa o número máximo de iterações do cálculo no fractal, ou seja, representa o número máximo de iterações
  a executar por cada ponto, no plano complexo, ao calcular se ele pertence ao conjunto. 
  Ela controla o detalhe do fractal. Valores maiores = mais precisão e mais tempo de cálculo.
  
  Nota: No cálculo de fractais cada ponto z do plano é iterado recursivamente até que |z| > 2 (diverge) ou até
  atingir c_max_iter.
  
  O valor será ajustado na função init_fractol().
  
f->color_mode = 0;

> Indica o modo da cor atual (controla o estilo da coloração do fractal, de 0 a 3).
  Permite alternar entre diferentes paletes ou algoritmos de cor com a tecla 'C'.

f->color_table = NULL;

> Representa a tabela com cores predefinidas para cada nível de iteração utilizada na coloração do fractal.
  É preenchida dinamicamente conforme c_max_iter e utilizada para colorir os pontos.
  É um array de ints (cores em hexadecimal), criado na função update_color_table().
  É inicializado com NULL pois ainda não existe nenhuma tabela de cores alocada.

f->zoom = 1.0

> Representa o nivel de zoom da visualização. Ela controla a escala da imagem. Quanto maior o zoom, mais "aproximado"
  está o plano complexo.
  Valor inicial: 1.0 -> sem zoom. Este valor é multiplicado/dividido quando fazemos o zoom com o rato.

f->offset_x = 0;
f->offset_y = 0;

> Representa o deslocamento da imagem no plano complexo.
  EStes valores são alterados ao mover a imagem com as teclas WASD ou com as setas
  Valor inicial: 0.0 -> (0,0) -> imagem centrada na origem.

f->julia_re = 0;
f->julia_im = 0;

> Representam as constantes reais e imaginárias utilizadas na fórmula da Julia.

f->pv.p.re = 0;
f->pv.p.im = 0;
f->pv.c.re = 0;
f->pv.c.im = 0;

> Representam os parâmetros da fórmula Phoenix:

  - pv.p: constante que representada o coeficiente que é multiplicada pelo valor anterior (z_{n-1}).
  - pv.c: constante que é somada em cada iteração.

Ambas são structs t_complex, com partes real e imaginária.
São inicializados com zero até que a função check_input() as defina.



1.2 - check_input()

void	check_input(t_fractol *f, int ac, char **av)
{
	if (ac == 2 && !ft_strcmp(av[1], "mandelbrot"))
		f->type = "mandelbrot";
	else if (ac == 4 && !ft_strcmp(av[1], "julia") && check_julia(av))  (1.2.1)
	{
		f->type = "julia";
		f->julia_re = ft_atof(av[2]);
		f->julia_im = ft_atof(av[3]);
	}
	else if (ac == 2 && !ft_strcmp(av[1], "burningship"))
		f->type = "burningship";
	else if (ac == 6 && !ft_strcmp(av[1], "phoenix") && check_phoenix(av))  (1.2.2)
	{
		f->type = "phoenix";
		f->pv.p.re = ft_atof(av[2]);
		f->pv.p.im = ft_atof(av[3]);
		f->pv.c.re = ft_atof(av[4]);
		f->pv.c.im = ft_atof(av[5]);
	}
	else
		exit_fractol(INPUT, f);
}


Esta função interpreta os argumentos da linha de comandos (ac e av) e:

- Determina qual fractal desenhar com base no input.
- Valida se os argumentos fornecidos são válidos (tanto em número como em conteúdo).
- Se os argumentos forem inválidos, termina imediatamente o programa com uma mensagem de erro.

> Verificação do tipo Mandelbrot:
  
  if (ac == 2 && !ft_strcmp(av[1], "mandelbrot"))
		f->type = "mandelbrot";

  Exige exatamente 2 argumentos:

    - av[0]: nome do executável ("./fractol").
    - av[1]: nome do fractal ("mandelbrot"). O segundo argumento (av[1]) tem de ser "mandelbrot".
  
  A função ft_strcmp compara as strings. !ft_strcmp(...) retorna verdadeiro se as strings forem iguais.
  Atribui a string "mandelbrot" a f->type, que será usada depois para desenhar o fractal correto na
  função de renderização (render_fractal).
  
  Para executarmos no terminal fazemos ./fractol mandelbrot
  
> Verificação do tipo Julia:

  else if (ac == 4 && !ft_strcmp(av[1], "julia") && check_julia(av))
  {
    f->type = "julia";
	  f->julia_re = ft_atof(av[2]);
	  f->julia_im = ft_atof(av[3]);
  }

  Exige 4 argumentos:

    - av[0]: nome do executável (""./fractol").
    - av[1]: nome do fractal ("julia").
    - av[2]: parte real da constante c.
    - av[3]: parte imaginária da constante c.

  A função check_julia() verifica se os dois valores estão dentro de um intervalo válido [-2.0, 2.0].
  Isto evita valores que tornem o fractal invisivel ou causem instabilidade numérica.

  int	check_julia(char **av)
  {
	  double	a;
	  double	b;

	  a = ft_atof(av[2]);
	  b = ft_atof(av[3]);
	  if ((a >= -2.0 && a <= 2.0) && (b >= -2.0 && b <= 2.0))
		  return (1);
	  else
		  return (0);
  }

  Se for válido: 

     - Atribui "julia" a f->type.
     - Converte os argumentos(strings) para double com o ft_atof() e armazena na:
     
       - f->julia_re: parte real da constante usada na fórmula do conjunto julia.
       - f->julia_im: parte imaginária.
       
       Estas constantes determinam a forma do fractal julia - diferentes valores resultam em padrões
       completamente diferentes.

  Para executarmos no terminal fazemos ./fractol julia <re> <im>

> Verificação do tipo Burning Ship:

  else if (ac == 2 && !ft_strcmp(av[1], "burningship"))
    f->type = "burningship";

  Exige exatamente 2 argumentos:

    - av[0]: nome do executável ("./fractol").
    - av[1]: nome do fractal ("burningship").

  A função ft_strcmp compara as strings. !ft_strcmp(...) retorna verdadeiro se as strings forem iguais.
  Atribui a string "burningship" a f->type, que será usada depois para desenhar o fractal correto na
  função de renderização (render_fractal).

  Este fractal tem uma aparência semelhante a um navio em chamas e é uma variação do Mandelbrot onde se
  usa o valor absoluto dos componentes complexos em cada iteração.

  Para executarmos no terminal fazemos ./fractol burningship

> Verificação do tipo Phoenix:

  else if (ac == 6 && !ft_strcmp(av[1], "phoenix") && check_phoenix(av))
  {
		f->type = "phoenix";
		f->pv.p.re = ft_atof(av[2]);
		f->pv.p.im = ft_atof(av[3]);
		f->pv.c.re = ft_atof(av[4]);
		f->pv.c.im = ft_atof(av[5]);
  }

  Exige 6 argumentos:

    - av[0]: nome do executável (""./fractol").
    - av[1]: nome do fractal ("phoenix").
    - av[2]: parte real de p.
    - av[3]: parte imaginária de p.
    - av[4]: parte real de c.
    - av[5]: parte imaginária de c.

  A função check_phoenix() verifica se os quatro valores estão dentro de um intervalo válido [-1.0, 1.0].
  
  Se for válido: 

     - Atribui "phoenix" a f->type.
     - Converte os argumentos(strings) para double com o ft_atof() e armazena na:
     
       - f->pv.p.re: parte real de p.
       - f->pv.p.im: parte imaginária de p.
       - f->pv.c.re: parte real de c;
       - f->pv.c.im: parte imaginária de c;
       
       Estas constantes determinam a forma do fractal phoenix - diferentes valores resultam em padrões
       completamente diferentes.
  
  Para executarmos no terminal fazemos ./fractol phoenix <p_re> <p_im> <c_re> <c_im>

> Mensagem de erro:

  else
    exit_fractol(INPUT, f);

  Se nenhuma das condições anteriores for satisfeita (ou porque faltam argumentos, ou o nome do fractal 
  está errado ou os valores estão fora do intervalo permitido) é chamada a função exit_fractol() com o
  código de erro INPUT.
  Termina o programa de forma segura e imprime uma mensagem de ajuda ao utilizador.
  
  


1.2.2 - check_phoenix()

static int	check_phoenix(char **av)
{
	double	p_re;
	double	p_im;
	double	c_re;
	double	c_im;

	p_re = ft_atof(av[2]);
	p_im = ft_atof(av[3]);
	c_im = ft_atof(av[4]);
	c_re = ft_atof(av[5]);
	if ((p_re >= -1.0 && p_re <= 1.0) && (p_im >= -1.0 && p_im <= 1.0)
		&& (c_re >= -1.0 && c_re <= 1.0) && (c_im >= -1.0 && c_im <= 1.0))
		return (1);
	else
		return (0);
}


1.2.3 - ft_atof()

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

double	ft_atof(const char *str)
{
	int		sign;
	double	nmb;
	int		power;

	nmb = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			sign = -1;
	}
	while (ft_isdigit(*str))
		nmb = nmb * 10 + (*str++ - '0');
	if (*str == '.')
		str++;
	power = 1;
	while (ft_isdigit(*str))
	{
		nmb = nmb * 10 + (*str++ - '0');
		power *= 10;
	}
	return (sign * nmb / power);
}


1.3 - init_fractol()

void	init_fractol(t_fractol *f)
{
	f->mlx = mlx_init();  (1.3.1)
	if (!f->mlx)
		exit_fractol(MALLOC, f);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, f->type);   (1.3.2)
	if (!f->win)
		exit_fractol(MALLOC, f);
	f->c_max_iter = MAX_ITER;    ([a])
	f->zoom = 1;                 ([b])
	update_color_table(f);   (1.3.3)
}


Esta função tem como objetivo:

- Iniciar a ligação com a MLX (a biblioteca gráfica usada), ou seja, podemos
  comunicar com o sistema gráfico.
- Criar uma janela de visualização, onde os fractais vão ser desenhados.
- Definir parâmetros essenciais do fractal (como número de iterações e zoom).
- Inicializar a tabela de cores usada para renderizar o fractal.


1.3.1 - Iniciar a ligação com a MLX

        f->mlx = mlx_init();
        
        A função mlx_init() inicia a conexão com o sistema gráfico do programa, iniciando a MiniLibx. 
        Em sistemas Unix, a função estabelece a ligação ao servidor gráfico X11, pelo o que, no processo, a função cria um contexto MLX (um handle) e
        devolve-o como um ponteiro void *, que contém e guarda tudo o que a MLX precisar para trabalhar ao longo do programa (desde a ligação ao servidor,
        formatos de píxel, etc). O ponteiro handle representa o contexto gráfico global da MLX, que vai ser utilizado em todas as funções da MLX 
        (como criar janelas, imagens, etc) e é por isso que temos de passá-lo a todas as outras funçoes da MLX.
        
        Guarda-se este valor em f->mlx.
        
        O ponteiro f aponta para a struct t_fractol (f é um ponteiro para uma struct t_fractol).
        f->mlx significa: "vai até à struct t_fractol que o ponteiro f aponta e acede ao campo mlx que está lá dentro".
        Nós passamos t_fractol *f às funções do Fract-ol, para que todas tenham acesso ao estado do programa: o handle da MLX (f->mlx), a janela (f->win), 
        a imagem, o zoom, etc.

        Ao executar f->mlx = mlx_init(), estamos a guardar no campo mlx (dentro da struct t_fractol apontada por f) o handle/contexto gráfico que a função
        mlx_init() devolve. Esse handle é o que permite que as operações da MiniLibx funcionem entre si.
       
        Quem recebe f e quem recebe f->mlx ?

        As funções (por exemplo, handle_key, render_fractal, init_fractol) recebem f para poderem ler/escrever o estado do programa.
        Como f é um ponteiro para a struct t_fractol, podemos passá-lo às funções (handlers), e dentro delas acedemos a f->mlx, f->win, etc, para chamar
        as funções da MLX que pedem esses handles. Assim, as funções da MLX não recebem f. Elas recebem os handles de que precisam, que tiramos de f para:

          - criar janelas: mlx_new_window(f->mlx, WIDTH, HEIGHT, title)
          - criar imagens: mlx_new_image(f->mlx, WIDTH, HEIGHT)
          - desenhar na janela: mlx_put_image_to_window(f->mlx, f->win, img, x, y)
          - registar/ligar eventos: mlx_key_hook(f->win, key_cb, f), mlx_mouse_hook(f->win, mouse_cb, f)
          - loop de eventos: mlx_loop(f->mlx)

        Sem este ponteiro (f->mlx), nada funciona graficamente.
        Sem este handle (f->mlx) não há contexto gráfico: não conseguimos criar janela/imagem, nem entrar no loop. 
        Por isso verificamos sempre se mlx_init() devolveu algo válido antes de continuarmos:
        
        if (!f->mlx)
	        exit_fractol(MALLOC, f);

        Verifica se a função mlx_init() conseguiu criar o contexto gráfico.
        Se falhar, é provavelmente por:
        
           - Falta de ligação ao servidor X11 (DISPLAY não definido)
           - Problemas com o sistema gráfico
           - Falta de memória
           
        Se mlx_init() falhar, ela retorna NULL, e assim qualquer chamada seguinte (por exemplo, criar 
        janela/imagem) iria rebentar. Assim, para evitar isso, o programa termina ao chamar exit_fractol()
        com o código de erro MALLOC.
        
1.3.2 - Criar a janela de renderização

        f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, f->type);

        A função mlx_new_window() tem como objetivo pedir ao sistema operativo para criar uma nova janela
        gráfica associada ao contexto gráfico da MLX (o handle) previamente iniciado com a função mlx_init(). 
        É nesta janela que vamos mostrar as imagens que vamos renderizar e desenhar no framebuffer (a t_img criada com a função mlx_new_image()).

        Ela recebe 4 parâmetros:

           - f->mlx: É ponteiro (handle), devolvido pela função mlx_init(), que contém a ligação ao servidor gráfico da MLX,
                    previamente criado, sendo obrigatório para a criação da janela. Sem este ponteiro não
                    se sabe onde nem como criar a janela, porque não tem ligação ativa com o servidor gráfico.
           - WIDTH: Corresponde à largura da janela, em píxeis. Define o número de colunas de píxeis que vão ser 
                    desenhadas por cada frame.
           - HEIGHT: Corresponde à altura da janela, em píxeis. Define o número de linhas de píxeis que vão ser
                     desenhadas por cada frame.
           - f->type: É a string (char *) que representa o tipo de fractal. Esta string contém o nome do fractal e é 
                      utilizada como título da janela, aparecendo na barra superior.

        Se a criação tiver sucesso, mlx_new_window() devolve um ponteiro/handle para a nova janela gráfica com dimensões 
        WIDTH x HEIGHT que será criada, onde os fractais vão ser desenhados.

        Janela ≠ Imagem (conceito importante): - Janela é o alvo onde vamos mostrar alguma coisa.
                                               - Imagem (t_img) é o framebuffer off-screen onde vamos desenhar píxel a píxel (com my_mlx_pixel_put).

        Ao executar f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, f->type), estamos a guardar no campo win (dentro da struct t_fractol apontada por f) 
        o handle/contexto gráfico que a função mlx_new_window() devolve.
        Esse handle será utilizado mais tarde para:

            - Desenhar imagens: mlx_put_image_to_window(f->mlx, f->win, img, 0, 0);
            - Configurar eventos: mlx_key_hook(f->win, handle_key, f);
                                  mlx_mouse_hook(f->win, handle_mouse, f);
            - Fechar a janela corretamente: mlx_destroy_window(f->mlx, f->win);

        Se não guardassemos f->win, ficariamos sem forma de colocar a imagem no ecrã, captar eventos ou fechar a janela
        sem leaks e, assim, não conseguiríamos interagir com a janela criada.

        if (!f->win)
	        exit_fractol(MALLOC, f);
        
        Garante que a janela foi criada com sucesso.
        Se mlx_new_window() falhar, significa que houve um erro, ou por:
        
             - Falta de memória no sistema.
             - Falha na ligação com o servidor gráfico.
             - Erro interno da MLX.
        
        Se falhar, a função retorna NULL e o programa termina de forma controlada com a função exit_fractol() que vai:
        
            - Libertar o que já foi alocado (imagens, tabela de cores, eventualmente a própria f->mlx, etc.).
            - Fechar a ligação ao contexto gráfico se existir.
            - Mostrar uma mensagem de erro adequada.
            - Terminar o programa com um exit code coerente.
        

[a] - f->c_max_iter = MAX_ITER;

      O ponteiro c_max_iter  da struct t_fractol representa o número máximo de iterações que o programa vai executar
      a fórmula matemática, do fractal, por cada ponto no ecrã.

      COmo funciona ? Ao desenharmos fractais como o Mandelbrot, Julia, Phoenix, etc, cada píxel do ecrã é associado a um ponto 
      específico do plano complexo. Para determinar a cor desse píxel, o programa aplica uma fórmula iterativa sobre esse ponto. 

      Exemplo para Mandelbrot: z = z² + c

      Onde: c representa a coordenada (ponto do plano complexo) associada ao píxel.
            z começa em 0 (0 + 0i) e é atualizado a cada iteração, com a fórmula.

      Para cada ponto, o programa aplica a fórmula repetidamente até: a sequência divergir (|z| > 2).
                                                                      ou atingir o limite de iterações definido 
                                                                      por c_max_iter.
                                                                      
      Se atingir o limite sem divergir, considera-se que o ponto pertence ao conjunto (ou está suficientemente perto para ser 
      considerado interior).

      Efeito na imagem:
      
      Um valor baixo de c_max_iter (ex: 30-50): serão feitos menos cálculos e, por sua vez, a renderização será mais rápida.
                                                O fractal terá menos detalhes, menos preciso e mais rápido.
      Um valor alto (ex: 500-1000): serão feitos mais cálculos e, por sua vez, a renderização será mais lenta (cada píxel faz 
                                    mais iterações). 
                                    O fractal terá muito mais detalhe nas zonas de fronteira, bordas mais suaves, transições de 
                                    cor mais suaves e mais preciso.

      Se MAX_ITER for definido com 100, isso significa que cada píxel (ponto) pode ser iterado até 100 vezes antes de decidir se
      ele pertence ou não ao conjunto do fractal.

      #define MAX_ITER 100

      Assim:  f->c_max_iter = MAX_ITER;

      Guarda esse valor inicial na struct, definindo o número máximo de iterações por cada ponto durante o cálculo do fractal.

      Relação com as cores: c_max_iter define quantos índices a tabela de cores (f->color_table) precisa.
                            Sempre que alterarmos c_max_iter (com as teclas O ou I), temos de reconstruir a tabela de cores 
                            ao chamar a função update_color_table(f).
                            Se iter == c_max_iter → píxel é pintado com a cor que representa o interior (normalmente preto).
      
[b] - f->zoom = 1;

      O ponteiro f->zoom (o campo zoom da struct t_fractol), representa o nível de ampliação da visualização do fractal.
      Ele define a escala da "câmara" sobre o plano complexo.
      O zoom controla a largura/altura da região vísivel e, por consequência, a resolução, em unidades complexas por pixel.
      
      Para que serve? O zoom ontrola o quão perto estamos do fractal, no plano complexo.
                      O valor do zoom é usado no cálculo que mapeia um píxel (x, y) da janela para o ponto (re, im), no plano.
                      Ou seja, o valor do zoom é usado no cálculo da conversão entre píxeis e coordenadas complexas.
                      Este valor pode ser modificado ao utilizar o scroll do rato ou as teclas de zoom.
                      O zoom afeta os limites do plano complexo que são mapeados para o ecrã.

      Mais à frente, na função ft_mapping, o mapeamento será feito assim:

       c_point.re = scale(x, -2.0 * f->zoom + f->offset_x,
                 2.0 * f->zoom + f->offset_x, WIDTH);
       c_point.im = scale(y, -2.0 * f->zoom + f->offset_y,
                 2.0 * f->zoom + f->offset_y, HEIGHT);

       A função scale() converte a posição do píxel para a posição correspondente no plano complexo, ajustando os limites visiveis
       com base no zoom e no offset.
       O zoom multiplica o tamanho da àrea vísivel do plano complexo:
      
          > Um zoom = 1: representa o nível base  (vista base) -> é o zoom normal (sem ampliação/zoom).
                         Iniciar com 1, garante que a primeira imagem apresentada é o enquadramento do fractal.
                         Com zoom = 1 (o nível base) → intervalo real e imaginário é [-2, 2] nos dois eixos -> pelo o que o span (a 
                         largura/altura da janela no plano complexo) é 4 em cada eixo (de -2 a 2).
      
          > Um zoom < 1: representa a aproximação (o zoom in). 
                         O intervalo dos valores visiveis no plano complexo encolhe -> aumentamos o detalhe ao entrar no fractal.
                         O span fica menor (ex. para um zoom = 0.5, o intervalo reduz para [-1, 1]) -> o span é 2 em cada eixo (de -1 a 1).
                         
          > Um zoom > 1: representa o afastamento (zoom out). 
                         O intervalo de valores visiveis no plano complexo aumenta -> vemos uma àrea maior (mostra mais área) mas com menos
                         detalhe ao afastar do fractal.
                         O span fica maior (ex. para um zoom = 2.0, o intervalo aumenta para [-4, 4]) -> o span é 8 em cada eixo (de -4 a 4.).

      Assim, quanto menor o zoom, mais perto estamos do fractol.

    O impacto do zoom nas iterações (c_max_iter)

      Nos fractais, a fronteira é onde uma minúscula variação do parÂmetro c altera o destino de se o ponto escapa ou não escapa para o infinito.
      Pontos muito perto da fronteira têm órbitas muito indecisas. Podem dar muitas voltas antes de finalmente divergirem para o infinito.
      Assim, o escape time (o tempo que o ponto demora a divergir/escapar) aumenta quanto mais nos aproximamos da fronteira.
      Há zonas com escape time muito lento, que exigem muitas iterações para decidir se diverge ou não.
    
      Quando aproximamos muito, chegamos a zonas de fronteira com dinâmica lenta, ou seja, ao aproximarmo-nos (zoom in) são reveladas fronteiras 
      onde as órbitas demoram mais a escapar (a órbita demora mais a “decidir” se escapa). 
      Se c_max_iter for baixo, muitos píxeis serão marcados como “interior” (preto) cedo demais, perdendo o detalhe, pelo o que é aconselhável aumentar
      c_max_iter para preservar o detalhe.

        - Com zoom < 1 (zoom in): o retângulo visivel encolhe -> cada píxel cobre uma região muito menor no plano complexo.
                                  Orbitas mais lentas e um escape time maior.
            
        - Com zoom > 1 (zoom out): vemos uma àrea grande -> cada píxel cobre uma região muito maior no plano complexo.
                                   Órbitas mais rápidas e um escape time médio-menor.

      Assim, ao aproximar (diminuir o zoom) de uma região fractal, aumentamos a densidade dos pixeis próximos da fronteira -> o render precisa de mais 
      iterações para classificar o escape time corretamente.
      Pelo contrário, ao afastar (aumentar o zoom) de uma região fractal, diminuimos a densidades dos píxeis próximos da fronteira -> o render precisa
      de menos iterações para classificar o escape time corretamente.

      > Caso c_max_iter seja baixo (e estamos a dar zoom): - Muitos pontos perto da fronteira que ainda não escaparam quando chegamos ao limte -> são
                                                             marcados como interior indevidamente.
                                                             Visualmente, perdemos detalhe, àreas que deviam mostrar nuances, mostram manchas escuras.
              
      > Se aumentamos o c_max_iter: - Damos tempo para que as órbitas lentas revelem o destino -> mais pontos corretamente coloridos (com indices altos de escape).
                                    - As fronteiras ficam definidas e as bandas ficam reduzidas.
                                      
    
    O impacto do zoom nas cores e por quê “recalcular”

      A cor é obtida através do indice n = nb_iter (número de iterações do fractal até escapar/divergir ou nb_iter == c_max_iter, se não escapar).
      QUando fazemos zoom:

      1) Recalculamos a imagem (sempre acontece)

         - Sempre que mudamos o zoom (ou offset), o mapeamento (x,y)→(Re,Im) altera → cada píxel cai noutro ponto do plano → o escape time muda → pelo o que 
           temos de recalcular a cor de todos os píxeis (o framebuffer inteiro).

      2) Recalculamos a tabela de cores / paleta (nem sempre)

         - A função update_color(), como vamos ver a seguir, reconstrói f->color_table[0..c_max_iter] apenas quando mudamos o modo da cor (f->color_mode), ou
           quando mudamos c_max_iter (porque o tamanho da tabela muda e a paleta distribui-se por outro limite).

      O zoom sozinho não obriga a recalcular a paleta das cores; mas obriga a recalcular a imagem, porque os índices nb_iter por píxel mudam.
      Em suma: ao fazer zoom, renderizamos sempre a imagem e só reconstruímos a paleta de cores se c_max_iter ou color_mode mudarem.

      Porque as cores alteram com o zoom?
      
      Mesmo com a mesma paleta de cores, o escape time nos píxeis muda (zonas escapam mais depressa/devagar), por isso o índice em color_table[nb_iter] muda → a cor 
      exibida muda.

      Como o zoom é alterado em tempo real? 
       
       O valor de zoom não é fixo — o utilizador pode alterá-lo durante a execução:

            - Scroll do rato: MOUSE_WHEEL_UP → multiplica zoom por um fator < 1 (aproxima).
                              MOUSE_WHEEL_DOWN → multiplica zoom por um fator > 1 (afasta).
                              A função zoom_at_point() garante que o ponto sob o cursor mantém-se no mesmo sítio do ecrã ao dar zoom.
            
            - O movimento da imagem (offset_x e offset_y) também é proporcional ao zoom, o que vai garantir um deslocamento suave em
              todos os níveis de aproximação.

        Impacto na renderização: Com zoom in (zoom < 1) -> Vemos menos área do fractal → mais detalhe local.
                                 Para manter a qualidade, muitas vezes é necessário aumentar c_max_iter (senão o interior fica preto muito cedo).

                                 Com zoom out (zoom > 1) -> Vemos mais área, mas o detalhe diminui. Pode-se reduzir c_max_iter para renderizar mais rápido.


1.3.3 - update_color()

void	update_color(t_fractol *f)
{
	int	i;

	if (f->color_table)
		free(f->color_table);
	f->color_table = malloc(sizeof(int) * (f->c_max_iter + 1));
	if (!f->color_table)
		exit_fractol(MALLOC, f);
	i = 0;
	while (i <= f->c_max_iter)
	{
		if (f->color_mode == 0)
			f->color_table[i] = polynomial_gradient(i, f->c_max_iter); (1.3.3.1)
		else if (f->color_mode == 1)
			f->color_table[i] = sin_gradient(i, f->c_max_iter);      (1.3.3.2)
		else if (f->color_mode == 2)
			f->color_table[i] = flame_gradient(i, f->c_max_iter);     (1.3.3.3)
		else if (f->color_mode == 3)
			f->color_table[i] = ocean_gradient(i, f->c_max_iter);      (1.3.3.4)
		else
			f->color_table[i] = BLACK;
		i++;
	}
}

    Para cada píxel do ecrã, calculamos um ponto no plano complexo e aplicamos a fórmula do fractal 
    (ex.: z = z² + c).
    Em cada iteração, verificamos se o valor de z é grande demais (na prática, se |z|² = z.re² + z.im² > 4).
    Se for maior que 4 antes de chegarmos ao limite de c_max_iter, dizemos que o ponto escapou (ou divergiu).
    Se nunca ultrapassar 4 até chegar ao limite c_max_iter, consideramos que esse ponto é um ponto interior 
    (pertence ao conjunto).

    O número de iterações que o ponto demorou até escapar (divergir) é o iter (também chamado de escape time).

    Portanto: iter ∈ [0, c_max_iter].
              iter == c_max_iter → interior (não escapou).
              iter < c_max_iter → exterior (escapou na iteração iter).

    Porque precisamos de uma paleta (tabela) de cores ?

    Durante a renderização, para cada píxel obtemos um iter, pelo o que precisamos de transformar esse iter numa
    cor RGB. Para fazer isso, pré-calculamos uma tabela com c_max_iter + 1 cores, onde a posição i guarda a cor correspondente 
    a “escapou em i iterações”. Esta é a função update_color(). 
    
    Vantagens: - A mesma iteração tem sempre a mesma cor, naquele modo.
               - Alterar o modo da cor ou do c_max_iter é só recriar a tabela apenas uma vez.
    
    Por que c_max_iter + 1?

    Quando renderizamos um fractal, para cada píxel calculamos quantas iterações (iter) o ponto demorou a "escapar" (escape time). 
    Esse iter é depois convertido numa cor RGB.

    O iter pode assumir todos os valores de 0 até c_max_iter, inclusive.
    Se criassemos um array com apenas c_max_iter posições, o último índice seria c_max_iter - 1.
    Mas se iter == c_max_iter (ponto interior), teriamos acesso fora dos limites (erro grave).
    Por isso, alocamos uma posição extra para este caso, garantindo que f->color_table[c_max_iter] existe.
    
    Assim, o iter pode assumir dois tipos de valores: - 0 até c_max_iter - 1 → pontos que escaparam antes do limite.
                                                      - c_max_iter → pontos que não escaparam (interior do fractal).

    Por isso: - Criamos c_max_iter + 1 posições, cada uma representando a cor para um número de iterações especifico.
                A posição i do array (f->color_table[i]) armazena a cor que vamos usar para todos os pontos que escaparem
                exatamente com i iterações.
              - A última posição (f->color_table[c_max_iter]) guarda a cor do interior, ou seja, guarda a cor para os pontos
               que nunca escapam (normalmente preto 0x000000). Assim, a última posição cobre o interior i == c_max_iter.
             
    Exemplo: c_max_iter = 100
             Logo, color_table tem 101 elementos: índices 0, 1, 2, ..., 100.

             Casos: O Ponto escapou cedo demais: Escapou à 15ª iteração → iter = 15 → cor = color_table[15]

             O Ponto nunca escapou: Não passou do raio até ao limite → iter = 100 → cor = color_table[100] (interior,
             normalmente preto).
    
    Recapitulando: Em vez de recalcular a cor RGB para cada píxel durante a renderização, pré-calcula-se uma tabela 
    (f->color_table) com c_max_iter + 1 cores. Cada posição i dessa tabela contém a cor a usar quando um ponto escapa
    exatamente em i iterações. A última posição (i == c_max_iter) é reservada para os pontos que nunca escapam, que representam
    o interior do fractal. 
    O tamanho é c_max_iter + 1, porque precisamos de uma cor para cada iter possível incluindo o “interior” (i == c_max_iter).    
    A paleta depende do modo da cor (color_mode): polinomial, sinusoidal, flame, ocean, etc.

    Exemplo: c_max_iter = 5:
    
    iter	            Significado	                 Cor (color_table[iter])
     0	       Escapou logo à primeira iteração	          Cor 0
     1	       Escapou à 2ª iteração	                    Cor 1
     2	       Escapou à 3ª iteração	                    Cor 2
     3	       Escapou à 4ª iteração	                    Cor 3
     4	       Escapou à 5ª iteração	                    Cor 4
     5 	       Nunca escapou (interior do fractal)	      Cor 5 (normalmente preto)

    
    A função update_color() é chamada sempre que alteramos:

         - f->c_max_iter (ex.: teclas O/I, mudamos a precisão) — porque o tamanho da paleta mudou.
         - f->color_mode (ex.: tecla C, mudamos o estilo) — porque a forma de colorir é outra.
                                                                                  
    A função update_color() (re)constrói a paleta f->color_table, com c_max_iter + 1 cores, que será usada na renderização. 
    Em vez de calcular a cor do "zero" para cada píxel, é pré-construído um array f->color_table com c_max_iter + 1 posições.

    Como esta paleta é usada na renderização?
    
    Na função update_color(), criamos a primeira paleta que será utilizada na função render_fractal().
    
    Na função render_fractal(): - Para cada píxel (x, y), fazemos o mapping para o plano complexo (c_point).
                                - Chamamos nb_iter = fractal_escape_time(f, &c_point). Esta função executa 
                                  o a fórmula do calculo do fractal e devolve o número de iterações iter em que escapou (ou 
                                  c_max_iter se não escapou).
                                - Para colorir, usamos a paleta de cores já pronta: color = f->color_table[nb_iter];
                                  Se o ponto nunca escapou, nb_iter == c_max_iter -> a paleta vai buscar color_table[c_max_iter],
                                  que corresponde à cor preta (interior).
                                  Se escapou cedo de mais -> nb_iter pequeno -> vai buscar cor de indices baixos (tipicamente tons
                                  claros conforme o gradiente).
                                  Se escapou tarde -> nb_iter grande -> cor mais profunda (próxima de c_max_iter - 1).
                                    
    Em suma, a função update_color() constrói (ou reconstrói) a paleta de cores f->color_table que o render_fractal() utiliza 
    para transformar o número de iterações de cada píxel numa cor RGB. 
    A função update_color() cria um array f->color_table (a paleta de cores) com c_max_iter + 1 cores, onde cada posição i corresponde
    à cor para um pixel que escapou em i iterações.
    Em vez de calcular a cor do "zero" para cada píxel, são pré-calculadas todas as cores possíveis uma única vez.
    Assim, com a função update_color() é construída (ou reconstruída) a paleta utilizada para pintar os píxeis UMA ÚNICA VEZ PARA
    TODAS AS POSSÍVEIS CORES para iter de 0 até c_max_iter + 1 (que será armazenado no array f->color_table). 
    Sem essa função, teriamos de recalcular as fórmulas de cor para cada píxel e cada frame;
    
    
    a) Verificar e libertar a tablea antiga

    O ponteiro f->color_table (paleta de cores) é onde guardamos todas as cores possíveis correspondentes aos valores da iteração iter de 0 até
    c_max_iter (inclusive) - ou seja, é onde guardamos todas as cores calculadas para cada valor da iteração (iter).
    Cada posição guarda uma cor no formato 0xRRGGBB.
    
    Ex.: f->color_table[15] é a cor para os “píxeis que escapam à 15.ª iteração”; 
         f->color_table[c_max_iter] é a cor do interior (não escapou).

    Quando f->color_table == NULL, ainda não foi alocada nenhuma paleta (ínicio do fract-ol ou depois de a termos libertado e 
    ainda não termos criado outra). Assim, quando f->color_table é NULL, significa que ainda não existe uma tabela alocada.
    
    Aqui:
    
    if (f->color_table)
        free(f->color_table);

    Podemos interpretar como: “Se já existe uma paleta (ou seja, o ponteiro não é NULL), temos de libertar antes de criar uma nova 
    (antes de alocarmos uma outra)”.

    Porquê que é necessário libertarmos? Se fizermos malloc para uma nova paleta de cores sem libertar a antiga, perdemos a referencia 
    ao bloco anterior, ou seja, se não dermos free(), vamos perder a referência para o array antigo quando apontarmos f->color_table para 
    um novo bloco de memória, o que causaria um memory leak.
    Como update_color() pode ser chamada várias vezes (mudança de cor, aumento de c_max_iter, etc.), esta libertação é essencial, pois sem 
    o free() iriamos acumular lixo na heap a cada chamada.
    
    A seguir, após libertarmos a tabela de cores anterior ficámos com um novo espaço vazio para preencher com as cores de acordo com o
    f->color_mode.
    Reservamos espaço para c_max_iter + 1 inteiros: - reservamos espaço para as cores dos pontos que escapam -> de 0 a c_max_iter - 1;
                                                    - e reservamos espaço para a cor do interior (ponto que não escapou) -> índice c_max_iter; (+ 1).

    Se o malloc falhar (se devolver NULL), não temos a paleta (tabela de cores), pelo o que o render tentará fazer f->color_table[iter] e vai rebentar,
    pelo o que temos de sair de forma controlada - exit_fractol(MALLOC, f) - exibindo a mensagem de erro e libertando os recursos antes de sair.

    Porquê que temos de dar exit ? Sem f->color_table não podemos renderizar nada, pois a função render_fractal() depende dela. 
    Em render_fractal(), fazemos color = f->color_table[nb_iter]; Se f->color_table == NULL, isso é acesso inválido → segfault.
    Continuar o programa sem f->color_table levaria a um segfault quando tentassemos fazer f->color_table[i].

    Cada chamada da função update_color() garante que temos uma paleta nova e consistente.

    b) Loop de preenchimento da tabela das cores (paleta)

    Até aqui, a função já garantiu que:

        - Qualquer paleta antiga foi libertada (free(f->color_table)),
        - Uma nova área de memória (malloc) foi reservada para c_max_iter + 1 posições (índices de 0 até c_max_iter),
        - E está pronta para preencher cada posição com a cor correspondente ao número de iterações.

    Agora, entramos no loop de preenchimento da tabela.
    
    Nesta parte queremos contruir (ou reconstruir) a paleta de cores f->color_table, onde cada indice i (que vai de 0 a c_max_iter)
    vai guardar a cor RGB a usar quando um píxel escapa ao fim de i iterações (e a última posição, i == c_max_iter, se não escapou).
    
    No while (i <= f->c_max_iter) estabelecemos que o limite é <= f->c_max_iter. 
    Por quê ? Porque precisamos de preencher todas as cores possíveis:
    
      - i: vai de 0 a c_max_iter - 1 -> representa os pontos que escapam antes do limite.
      - i == c_max_iter: representa o ponto em que não escapa (interior).
        
    Se usassemos "<" f->c_max_iter, ficavamos sem a última posição (interior), precisamente quando i == c_max_ter.
  
    Assim, o loop while vai de 0 até c_max_iter. A cada iteração do while, ou seja, para cada posição i, calculamos uma cor da paleta f->color_table[i],
    de acordo com o color_mode.

    O que é o color_mode? é um selecionador de paletas guardado na struct t_fractol.
    Ela indica que algoritmo da cor vamos usar para mapear o número de iterações iter para a respetiva cor.
    Normalmente é alterado por uma tecla (C): incrementamos e chamamos update_color() e é redesenhado.

    Dentro do while, para cada i, definimos f->color_table[i] - decidimos como colorir com base no modo f->color_mode.
    Consoante o color_mode, chamamos uma função da paleta.
    Passamos sempre o i atual (correspondente ao número de iterações do ponto até escapar) e o max_iter.
    O resultado devolvido pela função vai ser armazenado em f->color_table[i].
    Isto repete-se para todos os i de 0 até c_max_iter.
    
    if (f->color_mode == 0)
			f->color_table[i] = polynomial_gradient(i, f->c_max_iter); (1.3.3.1)
		else if (f->color_mode == 1)
			f->color_table[i] = sin_gradient(i, f->c_max_iter);      (1.3.3.2)
		else if (f->color_mode == 2)
			f->color_table[i] = flame_gradient(i, f->c_max_iter);     (1.3.3.3)
		else if (f->color_mode == 3)
			f->color_table[i] = ocean_gradient(i, f->c_max_iter);      (1.3.3.4)
		else
			f->color_table[i] = BLACK;
		i++;
        
    Se o modo da cor selecionado (f->color_mode) for 0, usamos a função polynomial_gradient().
    
    Todas as funções/algoritmos das cores são prototipadas como int nome_da_paleta(int i, int max_iter);

    - i: o número de iterações a que o ponto escapou (de 0 a max_iter). Quando i == max_iter, o ponto não escapou → interior.
    - max_iter: o limite máximo (valor de f->c_max_iter).
    - Valor de retorno: um int com a cor no formato 0xRRGGBB. O resultado (um int RGB no formato 0xRRGGBB) é armazenado em f->color_table[i].

    No fim do ciclo, temos um mapa completo “iteração → cor”:

        > f->color_table[0]: cor para os pontos que escapam instantaneamente.

        > f->color_table[c_max_iter - 1]: cor para pontos que escapam muito tarde (ficaram perto da fronteira).

        > f->color_table[c_max_iter]: cor do interior (os que não escaparam dentro do limite).
                                      Normalmente é preto, definido pela função do gradiente quando iter >= max_iter.

    Caso f->color_mode não corresponda a nenhum dos modos implementados, a cor por defeito é o preto (0x000000).
    Serve como fallback para evitar valores indefinidos.

    De seguida, avançamos para o próximo índice e repetimos o processo até preencher toda a paleta f->color_table.  

                                        
1.3.3.1 - polynomial_gradient()

int	polynomial_gradient(int iter, int max_iter)
{
	int		r;
	int		g;
	int		b;
	double	t;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / max_iter;
	r = (int)(9.0 * (1 - t) * t * t * t * 255.0);
	g = (int)(15.0 * (1 - t) * (1 - t) * t * t * 255.0);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255.0);
	return ((r << 16) | (g << 8) | b);
}

1.3.3.2 -  sin_gradient()

int	sin_gradient(int iter, int max_iter)
{
	int	r;
	int	g;
	int	b;
    double freq;
    double amp;

    freq = 0.07;
    amp = 110;
	if (iter == max_iter)
		return (0x000000);
	r = (int)(sin(freq * iter + 0.0) * amp + 128);
	g = (int)(sin(freq * iter + 2.1) * amp + 128);
	b = (int)(sin(freq * iter + 4.2) * amp + 128);
	return ((r << 16) | (g << 8) | b);
}

1.3.3.3 -  flame_gradient()

int	flame_gradient(int iter, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iter == max_iter)
		return (0x000000);
	t = (double)iter / (double)max_iter;
	r = (int)(pow(t, 0.7) * 255.0);
	g = (int)(pow(t, 1.3) * 180.0);
	b = (int)(pow(t, 2.0) * 80.0);
	return ((r << 16) | (g << 8) | b);
}

1.3.3.4 -  ocean_gradient()

int ocean_gradient(int iter, int max_iter)
{
    int r;
    int g;
    int b;
    double t;
    
    if (iter >= max_iter)
        return 0x000000;
    t = (double)iter / (double)max_iter;
    r = (int)(t * 50);
    g = (int)(t * 200 + 30);
    b = (int)(t * 255);
    return ((r << 16) | (g << 8) | b);
}




1.4 - render_fractal()

void	render_fractal(t_fractol *f)
{
	int			x;
	int			y;
	int			nb_iter;
	t_complex	c_point;
	int			color;

	if (f->img.img)
		mlx_destroy_image(f->mlx, f->img.img);    (1.4.1)
	init_image(f);                (1.4.2)
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			c_point = ft_mapping(x, y, f);
			nb_iter = fractal_escape_time(f, &c_point);
			color = colorize(nb_iter, f);
			my_mlx_pixel_put(&f->img, x, y, color);
		}
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);
}

A função render_fractal() é responsável por renderizar o frame completo do fractal na janela, com base nos parâmetros atuais (tipo de fractal,
zoom, offset_x/y, c_max_iter e color_mode).

Ela cria um framebuffer (que é um alvo de desenho na memória), onde os píxeis do fractal serão desenhados antes de serem exibidos na janela.

A função: - prepara um framebuffer off-screen (imagem na memória);
          - percorre todos os píxeis da janela;
          - para cada píxel, mapeia (x, y) para o plano complexo c_point = (re, im), ou seja, para cada píxel (x, y) converte do ecrã para as 
            coordenadas no plano complexo);
          - calcula o escape time: itera a fórmula do fractal para nos dar o número de iterações (nb_iter) até ao momento em que o ponto escapou.
          - converte esse número (nb_iter) na cor correspondente com a função my_mlx_pixel_put.
          - no fim, apresenta o framebuffer pronto na janela, de uma só vez com mlx_put_image_to_window.

A função render_fractal() é o “motor” visual do fract-ol. Sempre que mexemos (zoom/pan, troca de fractal, cor, iterações),
é ela que reflete imediatamente essas mudanças no ecrã.

a1) Variáveis

    int x: representa a coordenada horizontal do píxel atual que estamos a processar.
    int y: representa a coordenada vertical do píxel atual que estamos a processar.
    int nb_iter: guarda o número de iterações até o ponto divergir/escapar (escape time). É o escape time do ponto c_point (quantas 
                 iterações até divergir, ou atingir c_max_iter).
    t_complex c_point: é a representação do ponto no plano complexo (re, im) que corresponde ao píxel (x, y) atual.
    int color: é a cor final que será atribuída ao píxel (x, y) no framebuffer, com base no escape time e na paleta de cores.
    
a2) Reciclar a imagem anterior

    if (f->img.img)
        mlx_destroy_image(f->mlx, f->img.img);

    Se já existe uma imagem anterior (f->img.img), ela é destruída antes de criar outra. Isto é importante para evitar memory leaks,
    e garante que cada frame começa com um buffer limpo. Se não fizermos isto, a cada renderização, iriamos acumular imagens na memória,
    o que pode levar a um consumo excessivo de memória e eventualmente a falhas.
    
a3) 1.4 Inicializar a nova imagem: criar o framebuffer do frame atual (init_image(f))

    Quando o programa quer mostrar um novo estado do fractal (por exemplo, após um zoom, pan, mudança de cor ou alteração do tipo de fractal), 
    ele não desenha diretamente na janela. Em vez disso, cria um "framebuffer off-screen" — uma imagem temporária na memória — onde o fractal 
    será calculado e pintado píxel a píxel.
    Só depois de terminar esse desenho é que a imagem completa é enviada para a janela numa única operação, evitando cintilação (flicker).
    No Fract-ol, a criação desse framebuffer é feita pela função init_image().
    
    1.4.2 - init_image()

    void	init_image(t_fractol *f)
    {
	    t_img	new_img;

	    new_img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	    if (!new_img.img)
		    exit_fractol(MALLOC, f);
	    new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel,
			    &new_img.line_length, &new_img.endian);
	    if (!new_img.addr)
		    exit_fractol(MALLOC, f);
	    f->img = new_img;
    }

    A função init_image(f) é chamada para criar uma imagem MLX (um framebuffer na memória), com dimensões WIDTH X HEIGHT, onde vamos desenhar os
    pixeis do fractal atual antes de o exibir na janela, para que no fim, essa imagem seja enviada para a janela com mlx_put_image_to window.
    
    Ou seja, a função cria uma nova imagem MLX, na memória, para armazenar o frame atual do fractal, e configura a struct t_img com todos os dados
    necessários para manipular diretamente os píxeis dessa imagem, na memória - ou seja, configura a struct t_img com todos os dados necessários 
    para obter acesso direto à memória dos píxeis dessa iamgem.
    Essa nova imagem, que representa a imagem/frame atual, vai ser guardada no campo img (do tipo t_img) da struct t_fractol para o qual f aponta (f->img),
    para o render poder utilizá-la.
    
    A função init_image() é responsável por inicializar a struct de imagem (t_img) dentro da struct t_fractol, ou seja, vai preencher os campos de
    f->img (do tipo t_img) com os valores válidos.
    A struct t_fractol é usada para armazenar a imagem atual do fractal (f->img). 

    typedef struct s_img 
    {
      void *img;            // handle opaco da MLX para a imagem
      char *addr;           // ponteiro para os bytes dos píxeis
      int   bits_per_pixel; // bits por píxel (tipicamente 32)
      int   line_length;    // bytes por linha (stride), pode ter padding
      int   endian;         // endianness do armazenamento
    }       t_img;
    
    O que fica inicializado?
    
        - f->img.img : o handle (ponteiro void *) da imagem MLX criada;
        - f->img.addr : o ponteiro para o primeiro byte do buffer de píxeis (onde vamos escrever os valores das cores RGB);
        - f->img.bits_per_pixel, f->img.line_length, f->img.endian → são usados para calcular o endereço de cada píxel da imagem.

        
    É criada também uma struct temporária t_img chamada new_img, que é usada para inicializar a imagem do fractal e receber todos os dados
    da imagem (handle MLX, ponteiros para os píxeis, etc). No final, a imagem/frame atual é armazenada em f->img.

    Vantagem: permite inicializar a imagem de forma limpa e segura, garantindo que f->img sempre contém uma imagem válida, ou seja, só atualizamos 
              f->img quando a nova imagem é criada com sucesso.
 
              
    b1) Criar a imagem MLX

    new_img.img = mlx_new_image(f->mlx, WIDTH, HEIGHT);

    A função mlx_new_image() cria uma nova imagem com as dimensões WIDTH x HEIGHT (definidas no header) e retorna um handle (ponteiro void *) dessa
    imagem, que será armazenado em new_img.img.
    Ela pede ao MLX para alocar uma imagem na memória com as dimensões especificadas.

    Se a criação falhar (se retornar NULL), chamamos exit_fractol(MALLOC, f) para sair do programa de forma controlada, exibindo uma mensagem de erro.

    
    b2) Obter acesso à memória dos píxeis

    new_img.addr = mlx_get_data_addr(new_img.img, &new_img.bits_per_pixel, &new_img.line_length, &new_img.endian);

    A função mlx_get_data_addr() vai receber o handle da imagem criada (new_img.img) mais os três ponteiros para obter o endereço de memória onde os píxeis
    da imagem estão armazenados. 
    A função vai devolver um ponteiro (char *) para o ínicio do buffer de pixeis (o ponteiro vai apontar para o primeiro byte da primeira linha).
    A função mlx_get_data_addr() preenche:
    
        - new_img.bits_per_pixel: número de bits por píxel. Representa quantos bits ocupam os dados de cada píxel (normalmente 32 bits = 4 bytes → R, G, B, Alpha).
        - new_img.line_length: comprimento de uma linha da imagem em bytes (usado para calcular o deslocamento de cada linha). É o número total de bytes que cada
                               linha de píxeis ocupa na memória.
        - new_img.endian: indica a ordem dos bytes (endianness) da imagem na memória (0 para little-endian, 1 para big-endian). Indica, assim, a ordem com que os bytes
                          das cores estão organizados.
        
    Com estes dados, funções como my_mlx_pixel_put() conseguem calcular exatamente onde escrever a cor de cada píxel. E, assim, podemos calcular o endereço de cada píxel
    (x, y) na imagem, o que é essencial para desenhar os píxeis corretamente. É nessa função que o programa vai escrever os valores RGB de cada píxel do fractal.
        
    Se a obtenção do endereço falhar (se retornar NULL), também chamamos exit_fractol(MALLOC, f) para sair do programa de forma controlada.

    
    b3) Copiar a nova imagem para f->img

    f->img = new_img;

    Finalmente, depois de criada e configurada, a imagem temporária new_img é copiada para f->img, que é a imagem atual do fractal. 
    Assim, f->img passa a apontar para o framebuffer válido do frame atual e contém a nova imagem criada e pronta para ser usada.

    Resumo visual do processo

    - Criar uma folha em branco na memória (mlx_new_image).
    - Obter a caneta para desenhar diretamente nessa folha (mlx_get_data_addr).
    - Guardar tudo em f->img, que o resto do programa vai usar para: - Colocar cores píxel a píxel (my_mlx_pixel_put)
                                                                     - No final, mostrar essa folha pronta na janela (mlx_put_image_to_window).

                                                                     
    a4) Loop de renderização

    y = -1;
    while (++y < HEIGHT)
    {
        x = -1;
        while (++x < WIDTH)
        {
            ...
        }
    }
    
    O loop percorre todos os píxeis da imagem, de cima para baixo (y) e da esquerda para a direita (x).

    y = coordenada vertical (quantas linhas já descemos desde o topo).
    x = coordenada horizontal (quantas colunas já andamos desde a esquerda).

    Relação com o ecrã: (0,0)  → canto superior esquerdo
                        (1,0)  → move 1 pixel para a direita (mesma linha)
                        (0,1)  → move 1 pixel para baixo (mesma coluna)

    Portanto: y → linhas (varia de 0 a HEIGHT - 1)
              x → colunas (varia de 0 a WIDTH - 1)

    No fundo: HEIGHT = quantas linhas a imagem tem (altura, eixo vertical).
              WIDTH = quantas colunas a imagem tem (largura, eixo horizontal).
    
    Todos os píxeis são processados, desde o píxel (0, 0) no canto superior esquerdo até ao píxel (WIDTH - 1, HEIGHT - 1) no canto inferior direito.
    Todos os píxeis válidos da janela: (x, y) com 0 ≤ x < WIDTH, 0 ≤ y < HEIGHT.
    O par (x, y) é a coordenada de ecrã do píxel que vamos pintar.

    
    a5) Mapeamento do píxel para o plano complexo

    c_point = ft_mapping(x, y, f);

    t_complex	ft_mapping(int x, int y, t_fractol *f)
    {
	    t_complex	c_point;

	    c_point.re = scale(x, -2.0 * f->zoom + f->offset_x, 2.0 * f->zoom + f->offset_x, WIDTH);
	    c_point.im = scale(y, -2.0 * f->zoom + f->offset_y, 2.0 * f->zoom + f->offset_y, HEIGHT);
	    return (c_point);
    }

    No ecrã temos as coordenadas do píxel:

    (0,0)         → canto superior esquerdo
    (WIDTH - 1, 0)   → canto superior direito
    (0 , HEIGHT - 1)  → canto inferior esquerdo

    Mas o fractal não é calculado em píxeis — ele existe num plano complexo, onde cada ponto é: (re, im)  // real e imaginário
    A cada frame, o render_fractal precisa de converter cada píxel (x, y) para o ponto complexo (re, im) dentro desse plano complexo.

    Exemplo (sem zoom nem offset):

    Canto superior esquerdo: (-2, 2)
    Centro: (0, 0)
    Canto inferior direito: (2, -2)

    Portanto, para desenhar o fractal, temos de converter cada píxel (x, y) do ecrã para o ponto (re, im) correspondente.
    Isto é mapeamento de coordenadas, e é isso que o ft_mapping() faz.

    A função ft_mapping(x, y, f) converte as coordenadas do píxel (x, y) do ecrã para o ponto correspondente no plano complexo c_point = (re, im).
    Ou seja, a função vai pegar num pixel do ecrã (x, y) e transforma-o no ponto complexo correspondente (re, im), onde vamos aplicar a fórmula do 
    fractal. Para fazer o mapping, a função precisa de saber em que zona do plano estamos neste momento (zoom/pan) -> essa informação está em t_fractol *f.

    Porquê que a função recebe t_fractol *f ? 

    Porque o mapeamento depende do estado atual da câmara:

      - f->zoom: o quão afastada/próxima está a janela (escala do plano).
      - f->offset: onde está centrada a janela.

    Quando fazemos alguma alteração no zoom ou no deslocamento (offset), são os campos de t_fractol que alteram.
    Sem f, a função não saberia: - se estamos aproximados (zoom in) ou afastados (zoom out);
                                 - para que lado a imagem foi deslocada;
    
                                 
    A função ft_mapping() aplica a transformação necessária para mapear as coordenadas do ecrã para o plano complexo, considerando o zoom, offset e
    dimensões do fractal.
    Nós temos uma janela no plano complexo (por exemplo, de -2 a 2 no eixo real e de -2 a 2 no eixo imaginário), e queremos saber qual é o ponto complexo
    correspondente a cada píxel (x, y) na janela do ecrã.

    O ponteiro f->zoom (o campo zoom da struct t_fractol), representa o nível de ampliação da visualização do fractal.
    Ele define a escala da janela sobre o plano complexo. O zoom controla a escala da área visivel (quão grande/pequena é a distância que vemos, na janela).
    O zoom controla a largura/altura da região vísivel e, por consequência, a resolução, em unidades complexas por pixel.
      
    Para que serve? O zoom ontrola o quão perto estamos do fractal, no plano complexo.
                    O valor do zoom é usado no cálculo que mapeia um píxel (x, y) da janela para o ponto (re, im), no plano.
                      
      
      > Um zoom = 1: representa o nível base  (vista base) -> é o zoom normal (sem ampliação/zoom).
                     Iniciar com 1, garante que a primeira imagem apresentada é o enquadramento do fractal.
                     Com zoom = 1 (o nível base) → intervalo real e imaginário é [-2, 2] nos dois eixos -> pelo o que o span (a largura/altura
                     da janela no plano complexo) é 4 em cada eixo (de -2 a 2).
      
      > Um zoom < 1: representa a aproximação (o zoom in). 
                     O intervalo dos valores visiveis no plano complexo encolhe -> aumentamos o detalhe ao entrar no fractal.
                     O span fica menor (ex. para um zoom = 0.5, o intervalo reduz para [-1, 1]) -> o span é 2 em cada eixo (de -1 a 1).
                         
      > Um zoom > 1: representa o afastamento (zoom out). 
                     O intervalo de valores visiveis no plano complexo aumenta -> vemos uma àrea maior (mostra mais área) mas com menos
                     detalhe ao afastar do fractal.
                     O span fica maior (ex. para um zoom = 2.0, o intervalo aumenta para [-4, 4]) -> o span é 8 em cada eixo (de -4 a 4.).

      Assim, quanto menor o zoom, mais perto estamos do fractal.

      
    O papel da função scale():

    double	scale(double to_scale, double n_min, double n_max, double o_max)
    {
	    return (n_min + (n_max - n_min) * (to_scale - 0) / (o_max - 0));
    }

    A função scale() converte a posição do píxel para a posição correspondente no plano complexo, ajustando os limites visiveis
    com base no zoom e no offset.
    A função scale() pega na coordenada do pixel no ecrã e calcula a sua posição correspondente no plano complexo, considerando o zoom e o offset.
    
    Ela recebe três parâmetros:
    
        - to_scale: a coordenada do ecrã (x ou y) que queremos converter.
        - n_min: o valor mínimo do plano complexo que corresponde ao início da janela visível (ex.: -2.0 * zoom + offset_x).
        - n_max: o valor máximo do plano complexo que corresponde ao fim da janela visível (ex.: 2.0 * zoom + offset_x).
        - o_max: a dimensão do ecrã (WIDTH ou HEIGHT).

    Por exemplo: 

    É como se fosse uma regra de três que converte um valor de um intervalo para outro.

    to_scale → o valor a converter (ex.: o x do píxel)
    [0, o_max] → intervalo original (ex.: 0 até WIDTH)
    [n_min, n_max] → intervalo de destino (ex.: -2 até 2)

    Queremos converter x = 400 de [0, 800] para [-2, 2]:

    re = -2 + (2 - (-2)) * (400 / 800)
    re = -2 + (4) * 0.5
    re = 0

    Ou seja, o píxel do meio (400) no eixo X corresponde a 0 no plano complexo.


    O offset_x e offset_y são as coordenadas do centro da câmara no plano complexo.
    Sem offset (offset_x = 0 e offset_y = 0), a janela fica centrada na origem (0, 0).
    Eles controlam o centro (a posição) da área visivel (a janela).
    
    O Centro da câmera/vista = (offset_x, offset_y).
    Ao alterarmos o offset_x move a janela para a direita/esquerda no plano complexo;
    Ao alterarmos o offset_y move para cima/baixo.
    
    Assim, quando, por exemplo, pressionamos as teclas WASD para mover a câmara na janela, os valores do offset são alterados, e
    portanto observamos o deslocamento da câmara sobre o plano complexo.

    > Intervalo visivel no eixo real (re): [minX, maxX] = [-2.0 * zoom + offset_x, 2.0 * zoom + offset_x].
    > Intervalo visivel no eixo imaginário (im): [minY, maxY] = [2.0 * zoom + offset_y, 2.0 * zoom + offset_y].
    
    O offset_x desloca o intervalo no eixo real:

      - Sem offset: intervalo X = [-2, 2]
      - offset_x = 1 → intervalo X = [-1, 3] → a camara moveu-se para a direita.
      - offset_x = -1 → intervalo X = [-3, 1] → a camara moveu-se para a esquerda.

    O mesmo acontece com offset_y no eixo imaginário, só que no Y o movimento é para cima/baixo.

    Assim: - Aumentar offset_x desloca [minX,maxX] para a direita no plano complexo.
           - Aumentar offset_y desloca o intervalo [minY, maxX] para cima no plano complexo.
    
    No fract-ol, o enquadramento base (sem zoom e sem offset) é um quadrado [-2, 2] x [-2, 2], no plano complexo.
    
    O zoom e o offset definem a área visível do fractal, ou seja, a parte do plano complexo que estamos a ver na janela.
    O zoom altera o tamanho da área visível, enquanto o offset move essa área pelo plano complexo.

    Como o zoom e o offset entram no mapping e definem a área visível?

    No mapping, para converter um pixel (x, y) do ecrã num ponto complexo (re, im), a função ft_mapping() precisa de saber
    que intervalo do plano está visivel no momento atual - e isso depende do zoom e do offset.

      > Intervalo visivel no eixo real (re): [minX, maxX] = [-2.0 * zoom + offset_x, 2.0 * zoom + offset_x].
      
      > Intervalo visivel no eixo imaginário (im): [minY, maxY] = [2.0 * zoom + offset_y, 2.0 * zoom + offset_y].
    
      Pelo o que o mínimo e o máximo do intervalo que a câmara está a ver é:   minX = -2.0 * zoom + offset_x
                                                                               maxX =  2.0 * zoom + offset_x
                                                                               minY = -2.0 * zoom + offset_y
                                                                               maxY =  2.0 * zoom + offset_y

    - A função scale() mapeia x para [minX, maxX] e y para [minY, maxY]:  c_point.re = scale(x, minX, maxX, WIDTH);
                                                                          c_point.im = scale(y, minY, maxY, HEIGHT);

      Em que ocorre uma transformação nos intervalos de: - x ∈ [0, WIDTH]   →   re ∈ [minX, maxX]
                                                         - y ∈ [0, HEIGHT]  →   im ∈ [minY, maxY]

    - Assim, cada píxel (x, y) é convertido para o ponto complexo (c_point.re, c_point.im) dentro da área visível atual.


    Supondo: WIDTH = HEIGHT = 800
             zoom = 0.5 (aproximação)
             offset_x = 0.3 (deslocado à direita)
             offset_y = -0.2 (deslocado para baixo)

            Limites: minX = -2 * 0.5 + 0.3 = -1 + 0.3 = -0.7
                     maxX =  2*0.5 + 0.3 =  1 + 0.3 =  1.3
                     minY = -1 - 0.2 = -1.2 
                     maxY =  1 - 0.2 =  0.8

            Píxel (0, 0): re = scale(0, -0.7, 1.3, 800)  = -0.7  // mínimo do intervalo X -> canto superior esquerdo
                          im = scale(0, -1.2, 0.8, 800)  = -1.2  // mínimo do intervalo Y -> canto superior esquerdo

            Píxel (800, 800): re = 1.3 // Maximo do intervalo X -> canto inferior direito
                              im = 0.8  // Maximo do intervalo Y -> canto inferior direito

            Centro (400, 400): re = scale(400, -0.7, 1.3, 800) = 0.3   // exatamente o offset_x
                               im = scale(400, -1.2, 0.8, 800) = -0.2  // exatamente o offset_y

            Isto confirma: o centro da câmara é o (offset_x, offset_y) no plano complexo.

            
            
            
    a6) Cálculo do número de iterações até divergir/escapar

        nb_iter = fractal_escape_time(f, &c_point);

        A função fractal_escape_time(), consoante o algoritmo do fractal, calcula quantas iterações a órbita do ponto complexo c_point demora 
        até escapar/divergir. O número de iterações (nb_iter) é depois utilizado para escolhermos com que cor vamos pintá-lo (color = colorize(nb_iter, f)).
        Aqui, o ponto complexo c_point é o que obtivemos a partir do mapping do pixel (x, y).

        O que é a órbita ? 
        
        A órbita é a trajetória dos valores zn produzidos pela fórmula do fractal: z_n+1 = z_n^2 + c.
        A fórmula é uma recorrência: cada novo valor depende do valor anterior. 
        Se escolhermos um ponto inicial z0, obtemos uma sequência infinita de pontos complexos:  z0, z1 = z0^2 + c, z2 = z1^2 + c, z3 = z2^2 + c, ...
        Essa sequência é a órbita de z0 sob aplicação da formula z = z^2 + c.
        
        Cada vez que aplicamos a fórmula, obtemos um novo ponto zn. Cada novo ponto é um valor diferente no plano -> vai-se formar uma cadeia de pontos.
        Esta cadeia de pontos é o que chamamos de órbita.
        Se |zn| ficar maior do que 2, sabemos que a órbita diverge.

        Visualmente, são desenhados segmentos de reta que se ligam a cada ponto sucessivo da órbita. Para mostrar a órbita, são desenhadas
        linhas entre z_n e z_n+1.

        Quando o ponto c está fora do conjunto, a órbita cresce rapidamente → os pontos divergem/escapam para longe, formando linhas longas e inclinadas.
        Quando está perto da fronteira, a órbita pode oscilar ou demorar a escapar → as linhas aparecem como “zig-zags” dentro e fora da região colorida.

        Se c estiver no interior, a órbita fica limitada (normalmente em ciclos), e a linha desenhada fica presa numa pequena região.

        Se a sequência divergir (ir para infinito), os segmentos crescem cada vez mais e apontam para fora, atravessando a circunferência |z| = 2 (o circulo de escape)
        Visualmente, na figura, equivale a ver a linha ultrapassar a circunferencia de raio 2 centrado na origem.

        
        O que é o “escape time” ?

        Para cada ponto do plano complexo c_point = (re, im), aplicamos uma fórmula (dependendo do tipo do fractal). 
        Primeiro, inicializamos z, conforme o tipo de fractal, por exemplo, para o Mandelbrot z = 0, para Julia z = c_point.
        De seguida, iteramos a fórmula recursiva do fractal correspondente.
        Iteramos até ocorrer uma das duas condições: 
    
          - Se |z| > 2.0 (ou |z|² ≤ 4.0) -> o ponto “escapou”/divergiu (passou do raio de escape) -> devolvemos o número de iterações até onde divergiu.

          - Se atingimos max_iter sem escapar/divergir, assumimos que o ponto está dentro (ou próximo) do conjunto -> O ponto não divergiu até 
            c_max_iter -> devolvemos c_max_iter (corresponde ao ponto considerado interior).
    
        Assim, enquanto a norma de z for pequena (tipicamente |z|² ≤ 4.0) e ainda não atingirmos o limite c_max_iter, continuamos a iterar.

        O escape time de um ponto é o menor número de iterações n para o qual a sua órbita ultrapassa o raio de escape, ou seja, |zn| > 2.
        Se isso não acontecer antes de atingir o limite máximo de iterações (c_max_iter) define-se o escape time desse ponto como c_max_iter, pelo o que 
        o ponto está dentro do conjunto.
        
        É o menor número de iterações porque queremos medir a rapidez com que o ponto escapa/diverge e, porque, matematicamente, numa função quadrática, a 
        primeira ultrapassagem de 2 garante uma divergência - não faz sentido iterar mais além.
        
        O escape time mede o quão depressa a órbita diverge para o infinito sob a iteração da fórmula do fractal.

        > O papel da fronteira e a leitura do escape time:

          - Interior: pontos cuja órbita não escapa → nb_iter == c_max_iter.

          - Exterior (colorido): pontos cuja órbita escapa → nb_iter < c_max_iter.

          - Fronteira: é o contorno do fractal que separa o interior (órbitas limitadas) do exterior (órbitas que escapam).
                       Visualmente, as fronteiras aparecem como zonas de alto escape time (cores "profundas").
                       
                       > Longe da fronteira (exterior) ⇒ as órbitas tendem a crescer rápidamente -> o escape time é baixo (divergem rapidamente) ⇒ nb_iter pequeno.
                       > Perto da fronteira (ainda exterior) ⇒ as órbitas podem oscilar e andar às voltas muitas iterações antes de divergirem ⇒ o escape time é alto (divergem 
                         lentamente) -> nb_iter grande.
                       > Interior: a órbita é limitada -> nunca excede para lá da fronteira (|z| > 2).

    NOTA/OBSERVAÇÃO:
    
    Fórmula original do escape: |z| > 2.
    Ou seja, se o módulo de z (distância à origem) for maior que 2, já sabemos que a sequência vai divergir para infinito.
 
    Porquê usar |z|^2 > 4 em vez de |z| > 2 ? 
    
    Calcular |z| exige uma raiz quadrada: |z| = sqrt(zre^2 + zim^2)
    Mas para verificar a condição, não precisamos do valor exato do módulo, só de saber se passou de 2.
    Logo, em vez de calcular: sqrt(zre^2 + zim^2) > 2, podemos elevar ambos os lados ao quadrado: zre^2 + zim^2 > 4
    Isto evita a raiz quadrada → torna a função mais eficiente e rápida.
    (E como estamos a repetir isto milhões de vezes, faz bastante diferença em performance).

    Conclusão: As duas condições são equivalentes: |z| > 2 (mais legível matematicamente).
                                                   |z|² > 4 (mais eficiente em código).

            
    Porque é que o Escape Time é útil para desenharmos os fractais?

    Imaginemos um ecrã com as proporções 800x800.
    Cada píxel (x,y) é convertido para um ponto complexo c_point.
    
    Para cada c_point: Executamos o algoritmo respetivo do fractal e obtemos o escape_time → vai devolver o nº de iterações até escapar -> esse número serve
                       de índice para as cores.

    Assim: - Pontos que escapam cedo (baixo nb_iter) → correspondem a cores claras ou quentes.
           - Pontos que demoram muito (alto nb_iter) → cores mais escuras ou frias.
           - Pontos que nunca escapam (nb_iter == max_iter) → normalmente preto.

    Ao juntar todos os píxeis, obtemos a forma do fractal: - Interior = regiões pretas.
                                                           - Exterior = cores graduadas pela velocidade de escape.


    
    1.4.4 - fractal_escape_time()

    int	fractal_escape_time(t_fractol *f, t_complex *c_point)
    {
	    int			nb_iter;
	    t_complex	c;

	    nb_iter = 0;
	    c.re = c_point->re;
	    c.im = c_point->im;
	    if (ft_strcmp(f->type, "mandelbrot") == 0)
		    nb_iter = mandelbrot(c, f->c_max_iter);
	    else if (ft_strcmp(f->type, "julia") == 0)
	    {
		    c.re = f->julia_re;
		    c.im = f->julia_im;
		    nb_iter = julia(c, *c_point, f->c_max_iter);
	    }
	    else if (ft_strcmp(f->type, "burningship") == 0)
		    nb_iter = burning_ship(c, f->c_max_iter);
	    return (nb_iter);
    }

    Dado o contexto do ponteiro f da struct t_fractol (que contém qual o fractal está ativo, o número máximo de iterações, os parÂmetros, etc) e 
    o ponto complexo c_point correspondente ao pixel (x, y), a função fractal_escape_time() calcula o número de iterações até divergir ou atingir
    o limite, para esse ponto, utilizando a fórmula do fractal selecionado. O inteiro que será devolvido no final (nb_iter) é depois utilizado para
    escolher a cor do píxel.

    A função recebe t_fractol *f porque precisa do estado atual do render para saber como calcular o escape time daquele pixel.
    A função fractal_escape_time() precisa do que está dentro do ponteiro f:

      > Qual fractal está ativo → f->type (decide qual função chamar: mandelbrot, julia, burningship).
      > Limite de iterações → f->c_max_iter
      > Parâmetros do fractal selecionado -> Julia: f->julia_re, f->julia_im.
                 
  
    No Fract-ol, t_complex é uma struct que guarda um número complexo:

    typedef struct s_complex 
    {
      double re;  // parte real
      double im;  // parte imaginária
    } t_complex;

    t_complex *c_point é um ponteiro para a struct t_complex.
    POnteiro = variável que guarda o endereço de outra coisa na memória

    Nós obtivemos o valor do c_point em ft_mapping(), em que o c_point corresponde ao ponto do plano complexo mapeado a partir do píxel (x,y).
    É o ponto no plano complexo correspondente ao píxel (x, y) atual.
    
    No calculo da função ft_mapping(): - c_point->re: corresponde à parte real (eixo horizontal do plano).
                                       - c_point->im: corresponde à parte imaginária (eixo vertical do plano).

    Para p ponteiro c_point aceder aos campos da struct t_complex, desreferenciamos primeiro o ponteiro e usamos "->":
    
      - c_point->re : acede a parte real do ponto do pixel, na struct t_complex.
      - c_point->im : acede a parte imaginária do ponto do pixel, na struct t_complex.


    O que é a variável t_complex c ?

    A variável temporária c é utilizada para representar o parâmetro c da fórmula do fractal, na chamada atual.
    Define o ambiente (o fractal) em que a órbita vai crescer.

    Quase todos os fractais são variantes da mesma forma iterativa: Z_{n+1} = f(z_n, c).

      - z_n representa o estado atual da órbita (é um número complexo).
      
      - c é um parâmetro constante (também é um número complexo) que pode ser: - fixo (o mesmo para todos os píxeis, ex: Julia);
                                                                               - ou variar conforme o píxel (ex: Mandelbrot, Burning ship);
            
      - z0 corresponde ao estado inicial da órbita (é o primeiro valor da sequência). 
        Este pode ser: - z0 = 0 (Mandelbrot, Burning Ship)  -> todo o teste começa do zero, o que muda de pixel para pixel é o c.
                       - z0 = c_point (Julia)  -> o parâmetro c é fixo, o que muda é o ponto de partida (z0).
                            
    O que define que fractal estamos a desenhar é como escolhemos z_0 (estado inicial) e, como definimos o parâmetro c.

    A grande diferença entre Mandelbrot, Julia e o Burning Ship está em: - Como escolhemos o parâmetro c ? Vem do píxel (c_point) ou é fixo ?
                                                                         - Qual é o estado inicial z_0 ? Sempre 0 ou começa no pixel ?
    
    Porquê que copiamos c_point para a variável c?  -> Para inicializar o parâmetro c com o valor do píxel ! 
    
    Como vimos em cima, em alguns fractais, o parâmetro c é exatamente o ponto do pixel mapeado (c = c_point), o que acontece com o Mandelbrot e o BUrning ship.
    Neste caso, como o próprio pixel no plano complexo (c_point) corresponde ao parâmetro c, cada píxel vai testar um c diferente.
    
    Noutro caso, como o da Julia, o parâmetro c não é o ponto do píxel mapeado, ele é fixo (veio da linha de comandos e está guardado em f->julia_re/im).
    Nesse caso, sobrescrevemos a variável temporária e alteramos o parametro c para o valor fixo: c.re = f->julia_re;   // c deixou de ser o ponto do pixel: agora é fixo - escolhido pelo utilizador
                                                                                                  c.im = f->julia_im;
                                                        
    E mantemos o *c_point intacto para passá-lo como estado inicial z0 na Julia:  nb_iter = julia(c, *c_point, f->c_max_iter);
                                                                                                   ^      ^       
                                                                                                   |      |       
                                                                                           parâmetro c   z0 = ponto do píxel
    Assim, todos os píxeis do Julia usam o mesmo parâmetro c.

                                                
    O que é a órbita ? 
        
        A órbita é a trajetória dos valores zn produzidos pela fórmula do fractal: z_n+1 = z_n^2 + c.
        A fórmula é uma recorrência: cada novo valor depende do valor anterior. 
        Se escolhermos um ponto inicial z0, obtemos uma sequência infinita de pontos complexos:  z0, z1 = z0^2 + c, z2 = z1^2 + c, z3 = z2^2 + c, ...
        Essa sequência é a órbita de z0 sob aplicação da formula z = z^2 + c.

        No Mandelbrot, começamos sempre com z0 = 0 e o parâmetro c é como se fosse o ponto do rato.
        Cada vez que aplicamos a fórmula, obtemos um novo ponto zn. Cada novo ponto é um valor diferente no plano -> vai-se formar uma cadeia de pontos.
        Esta cadeia de pontos é o que chamamos de órbita.
        Se |zn| ficar maior do que 2, sabemos que a órbita diverge.

        Visualmente, são desenhados segmentos de reta que se ligam a cada ponto sucessivo da órbita. Para mostrar a órbita, são desenhadas
        linhas entre z_n e z_n+1.

        Quando o ponto c está fora do conjunto de Mandelbrot, a órbita cresce rapidamente → os pontos divergem/escapam para longe, formando linhas longas e inclinadas.
        Quando está perto da fronteira, a órbita pode oscilar ou demorar a escapar → as linhas aparecem como “zig-zags” dentro e fora da região colorida.

        Se c estiver dentro do Mandelbrot, a órbita fica limitada (normalmente em ciclos), e a linha desenhada ficaria presa numa pequena região.

        Se a sequência divergir (ir para infinito), os segmentos crescem cada vez mais e apontam para fora, atravessando a circunferência |z| = 2 (o circulo de escape)
        Visualmente, na figura, equivale a ver a linha ultrapassar a circunferencia de raio 2 centrado na origem.


        
    > Verificar se o fractal é o Mandelbrot

        if (ft_strcmp(f->type, "mandelbrot") == 0)
		    nb_iter = mandelbrot(c, f->c_max_iter);

        - Verificamos se o fractal atualmente selecionado é o Mandelbrot.
        - f->type é uma string armazenada dentro da struct t_fractol (por exemplo: "mandelbrot", "julia", "burningship").
        - ft_strcmp(a, b) retorna 0 quando as strings são iguais.

        Logo: se o utilizador pediu para renderizar Mandelbrot, esta condição é verdadeira.

        Caso ft_strcmp é 0, ou seja, se as duas strings são iguais, chamamos o algoritmo do fractal mandelbrot (nb_iter = mandelbrot(c, f->c_max_iter))
        para calcular quantas iterações demorou até escapar (ou, se não escapou, nb_iter == c_max_iter). 

        São passados dois parâmetros: - c → o ponto complexo atual (coordenada do píxel no plano complexo).
                                      - f->c_max_iter → número máximo de iterações a realizar.

        O retorno (nb_iter) é o escape time → quantas iterações demorou até escapar ou, se não escapou, será c_max_iter.

    
        1.4.4.1 - mandelbrot()

        int	mandelbrot(t_complex c, int c_max_iter)
        {
	        t_complex	z;
	        int			nb_iter;

	        i = 0;
	        z.re = 0;
	        z.im = 0;
	        while (nb_iter < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	        {
		        z = c_add(c_mult(z, z), c);
		        nb_iter++;
	        }
	        return (nb_iter);
        }

        A função mandelbrot() calcula o escape time de um ponto c (c = c_point), no plano complexo.
        O valor devolvido é o número de iterações até a órbita escapar (|z| > 2), ou ,até atingir o limite máximo (c_max_iter).

        A Fórmula iterativa que define o conjunto do fractal Mandelbrot é: z_{n+1} = z_n^2 + c

        - z_n é o valor atual da sequência (é número complexo). É o valor atual da órbita na iteração n.
        
        - c é o ponto do plano associado ao píxel. 
          c = c_point -> vem do píxel (x, y) → (parte real = posição x no plano, parte imaginária = posição y).
          Por isso fazemos: c.re = c_point->re;
                            c.im = c_point->im;
          Aqui estamos a dizer:  “Para este píxel (x,y), o parâmetro c vai ser a sua posição no plano complexo.”
          Por exemplo, se o píxel representa a coordenada (-0.75, 0.1) então c = -0.75 + 0.1i .
          
        - z0 é o estado inicial da sequência/órbita - sempre começa em 0 (z0 = 0).

        A pergunta que se coloca no Mandelbrot é: “Se eu começar em z = 0 e aplicar repetidamente  z_{n+1} = z_n² + c, escapo para o 
                                                   infinito ou fico limitado?”

        Se a sequência divergir (|z| → ∞), ou seja, escapar para o infinito, o ponto não pertence ao conjunto.
        Se a sequência permanecer limitada (|z| nunca ultrapassa 2), o ponto pertence ao conjunto de Mandelbrot.

        É por isso que dizemos que o conjunto de Mandelbrot é o conjunto dos pontos c (no plano complexo) que não escapam/divergem.

        Assim, o conjunto de Mandelbrot é o conjunto de todos os pontos (c ∈ C) tais que a sequência não diverge (fica limitada, |z| ≤ 2) 
        após infinitas iterações.

        Na prática, se em algum n tivermos |z_n| > 2, a órbita vai divergir; se após um número grande de iterações (c_max_iter) ainda |z_n| <= 2, tratamos c 
        como interior (ou muito próximo) do conjunto de Mandelbrot.

        > Operações com números complexos: 

            Se a = x + yi e b = u + vi, então:

            > Módulo: |a| = sqrt(x^2 + y^2) e |a|^2 = x^2 + y^2
            > Soma: a + b = (x + u) + (y + v)i
            > Produto: a * b = (x * u - y * v) + (x * v + y * u)i
            > Para o quadrado de z (z²), com z = x + yi, temos: z^2 = (x^2 - y^2) + (2 * x * y)i 

        > Estado inicial do Mandelbrot (z0 = 0 + 0i)

            z.re = 0;
            z.im = 0;
            nb_iter = 0;

            Isto é especifico do Mandelbrot: sempre começamos com z = 0 (z0 = 0).

        > COndição de escape (divergência)

            while (nb_iter < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)

            A iteração só continua se: - Ainda não atingimos o máximo de iterações (nb_iter < c_max_iter) → isto garante que o cálculo termina (mesmo para pontos interiores).

                                       - O valor de |z|^2 = z.re^2 + z.im^2 ainda é ≤ 4.0 → porque se |z| > 2, a sequência diverge para o infinito.

            Ou seja, o while continua enquanto não antigimos o limite (nb_iter < c_max_iter) e |z|^2 <= 4 (equivale a |z| <= 2).
            Se |z| > 2, a órbita diverge.

            
        > Cálculo de z = c_add(c_mult(z, z), c);

            Aqui, aplicamos a fórmula: z_{n+1} = z_n^2 + c

            > c_mult(z, z) calcula z² = (z.re + z.im)^2

            [a] - c_mult()

            t_complex	c_mult(t_complex a, t_complex b)
            {
	            t_complex	res;

	            res.re = a.re * b.re - a.im * b.im;
	            res.im = a.re * b.im + a.im * b.re;
	            return (res);
            }

            Como vimos o produto é (x+iy)(u+iv) = (x * u - y * v) + (x * v + y * u)i
     
            Ou seja -> z^2 = ((z.re^2 - z.im^2) + (z.re * z.im + z.im * z.re))
                       z^2 = (z.re^2 - z.im^2) + (2 * (z.re * z.im))
               
                       Pelo o que z^2 = (z.re^2 - z.im^2) + (2 * (z.re * z.im))i
    
            > c_add(..., c) soma o parametro c = c.re + c.im

            [a] - c_add()

            t_complex	c_add(t_complex a, t_complex b)
            {
	            t_complex	res;

	            res.re = a.re + b.re;
	            res.im = a.im + b.im;
	            return (res);
            }

            Como vimos, a soma: (x+iy) + (u+iv) = (x + u) + (y + v)i

            Pelo o que fica z_{n+1} = (z.re^2 - z.im^2 + c.re) + (2 * (z.re * z.im) + c.im)i

            Isto dá-nos o novo valor de z, pronto para a próxima iteração.

        > Cada vez que aplicamos a fórmula, avançamos uma iteração (nb_iter++).
          No fim, nb_iter indica quantas vezes conseguimos iterar antes de escapar.

        > Se nb_iter < c_max_iter → o ponto escapou em nb_iter iterações.
          Se nb_iter == c_max_iter → o ponto não escapou → consideramos que pertence (ou está próximo) ao conjunto de Mandelbrot.


    > Verificar se o fractal é o Julia

        else if (ft_strcmp(f->type, "julia") == 0)
        {
            c.re = f->julia_re;
            c.im = f->julia_im;
            nb_iter = julia(c, *c_point, f->c_max_iter);
        }
        
        - Verificamos se o fractal atualmente selecionado é o Julia.
        - f->type é uma string armazenada dentro da struct t_fractol (por exemplo: "mandelbrot", "julia", "burningship", "phoenix").
        - ft_strcmp(a, b) retorna 0 quando as strings são iguais.

        Logo: se o utilizador pediu para renderizar o Julia, esta condição é verdadeira.

        Julia usa a mesma fórmula do Mandelbrot, mas troca o papel: - No fractal Mandelbrot, o que muda de pixel para píxel é o c. O parametro c 
                                                                      (c = c_point) varia e z0 é sempre 0.
                                                                    - No fractal Julia, c é sempre o mesmo → o que muda de píxel para píxel é z0.
                                                                      z0 varia (z0 = c_point).

        No fractal Julia, c não é o ponto do píxel — c é fixo (vem dos argumentos f->julia_re/julia_im), pelo que cada valor fixo de c dá origem 
        a um fractal JUlia diferente. Por isso, antes de chamarmos o fractal Julia, sobrescrevemos c e copiamos/armazenamos para evitar estar sempre
        a desreferenciar o ponteiro:  c.re = f->julia_re;
                                      c.im = f->julia_im;

        E passamos o ponto do píxel como z0 (estado inicial) na chamada julia(c, *c_point, ...).

        Assim, definimos o parâmetro fixo c da Julia (f->julia_re e f->julia_im), que foram lidos dos argumentos quando o utilizador executou 
        o programa: por exemplo ./fractol julia -0.7 0.27015. 

        Então c = -0.7 + 0.27015i, significa que todo o fractal Julia será construído com este mesmo parâmetro c.
        Alterar este valor muda completamente a forma do fractal, porque cada valor de c define um conjunto Julia diferente.

        Caso ft_strcmp é 0, ou seja, se as duas strings são iguais, definimos o parâmetro fixo da fórmula Julia e chamamos o algoritmo
        do fractal julia (nb_iter = julia(c, *c_point, f->c_max_iter)) para calcular quantas iterações demorou até escapar (ou, se não escapou,
        nb_iter == c_max_iter). 

        Na função julia() são passados três parâmetros: - c → o parâmetro fixo (vem do utilizador).
                                                        - c_point -> o ponto do plano complexo que corresponde ao pixel atual. Este será o estado inicial da iteração (z0).
                                                          Exemplo: se estamos a pintar o píxel (x=300, y=200), este é convertido em c_point = -0.12 + 0.85i.
                                                          Então começamos a órbita em z0 = -0.12 + 0.85i .
                                                        - f->c_max_iter → número máximo de iterações a realizar.

        O retorno (nb_iter) é o escape time → quantas iterações demorou até escapar ou, se não escapou, será c_max_iter.
 
       
        1.4.4.2 - julia()

        int	julia(t_complex c, t_complex z, int c_max_iter)
        {
	        int	nb_iter;

	        nb_iter = 0;
	        while (nb_iter < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	        {
		        z = c_add(c_mult(z, z), c);
		        nb_iter++;
	        }
	        return (nb_iter);
        }

        A função julia() calcula o espace time de um ponto incial z0 (o pixel mapeado) no conjunto Julia associado a um parâmetro fixo c.
        Ela devolve o número de iterações até a órbita ultrapassar o raio do escape (|z| > 2) - ou seja, até divergir, ou atingir o limite
        de c_max_iter.

        A fórmula da Julia é igual à do Mandelbrot: z_{n+1} = z_n^2 + c.

        Como vimos, no Mandelbrot, z0 = 0 e c = c_point (pixel).
        Por outro lado, no JUlia, z0 = c_point (pixel) e c é fixo (são lidos os argumentos).

        c — o parâmetro fixo do conjunto de Julia. Vem de f->julia_re/im (ex.: ./fractol julia -0.7 0.27015 ⇒ c = -0.7 + 0.27015i)

        z — é o estado inicial z0, que é o ponto do plano complexo correspondente ao píxel atual (c_point do mapping).

        c_max_iter — é o limite de iterações para decidir a cor/classificação.

        > COndição de escape (divergência)

            while (nb_iter < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)

            A iteração só continua se: - Ainda não atingimos o máximo de iterações (nb_iter < c_max_iter).
                                       → isto garante que o cálculo termina (mesmo para pontos interiores).

                                       - O valor de |z|^2 = z.re^2 + z.im^2 ainda é ≤ 4.0.
                                       → porque se |z| > 2, a sequência diverge para o infinito.
                                       
                                       Ou seja, o while continua enquanto não antigimos o limite (nb_iter < c_max_iter) e 
                                       |z|^2 <= 4 (equivale a |z| <= 2)
                                       Se |z| > 2, a órbita diverge.

        > Cálculo de z = c_add(c_mult(z, z), c);

            Aqui, aplicamos a fórmula: z_{n+1} = z_n^2 + c

            > c_mult(z, z) calcula z² = (z.re + z.im)^2

            [a] - c_mult()

            t_complex	c_mult(t_complex a, t_complex b)
            {
	            t_complex	res;

	            res.re = a.re * b.re - a.im * b.im;
	            res.im = a.re * b.im + a.im * b.re;
	            return (res);
            }

            Como vimos o produto é (x+iy)(u+iv) = (x * u - y * v) + (x * v + y * u)i
     
            Ou seja -> z^2 = ((z.re^2 - z.im^2) + (z.re * z.im + z.im * z.re))
                       z^2 = (z.re^2 - z.im^2) + (2 * (z.re * z.im))
               
                       Pelo o que z^2 = (z.re^2 - z.im^2) + (2 * (z.re * z.im))i
    
            > c_add(..., c) soma o parametro c = c.re + c.im

            [a] - c_add()

            t_complex	c_add(t_complex a, t_complex b)
            {
	            t_complex	res;

	            res.re = a.re + b.re;
	            res.im = a.im + b.im;
	            return (res);
            }

            Como vimos, a soma: (x+iy) + (u+iv) = (x + u) + (y + v)i

            Pelo o que fica z_{n+1} = (z.re^2 - z.im^2 + c.re) + (2 * (z.re * z.im) + c.im)i

            Isto dá-nos o novo valor de z, pronto para a próxima iteração.

        > Cada vez que aplicamos a fórmula, avançamos uma iteração (nb_iter++).
          No fim, nb_iter indica quantas vezes conseguimos iterar antes de escapar.

        > Se nb_iter < c_max_iter → o ponto escapou em nb_iter iterações.
          Se nb_iter == c_max_iter → o ponto não escapou → consideramos que pertence (ou está próximo) ao conjunto de Julia.

        > Para cada píxel (portanto, para cada z0 distinto):

            - Fixamos o mesmo c (todo o fractal Julia utiliza o mesmo c). 
            - Criamos a órbita: z0, z1 = fc(z0), z2 = fc(z1), …
            - Se a órbita escapa/diverge (passa o círculo de raio 2), colorimos pelo escape time.
            - Se não escapa/diverge até c_max_iter, consideramos que z0 pertence ao conjunto de JUlia (o conjunto preenchido de JUlia),
              pelo o que se pinta a preto.


         A diferença entre Mandelbrot e Julia: > Mandelbrot: - z0 = 0 (estado inicial fixo em todos os pontos).
                                                             - c = c_point (vem da posição do píxel).
        
                                                             Cada ponto no plano representa um parâmetro c diferente.

                                               > Julia: - z0 = c_point (o píxel agora é o estado inicial).
                                                        - c é fixo (escolhido pelo utilizador).
              
                                                        Cada ponto no plano responde à pergunta: “Com este ponto (estado) inicial a órbita 
                                                        diverge ou não ?”.
                                                        Um único c cria um conjunto Julia inteiro.

        Relação com o Mandelbrot

        Cada ponto c do Mandelbrot está associado a um conjunto Julia.
        Se c está dentro do Mandelbrot, a Julia correspondente é conexa.
        Se c está fora do Mandelbrot, a Julia correspondente é desconexa (um pó de pontos espalhados).
        É por isso que o Mandelbrot é chamado o “mapa das Julias”.
               
        O Mandelbrot é como um “mapa de parâmetros” dos conjutos Julia -> cada ponto c no Mandelbrot corresponde a um fractal Julia.
        
        Se não fixássemos o parâmetro c no JUlia, estaríamos simplesmente a calcular outra coisa qualquer (provavelmente um Mandelbrot de novo).
        Se não usássemos o píxel como z0 (z0 = c_point), não veríamos a riqueza do conjunto de Julia.

        
    > Verificar se o fractal é o Burning Ship

        else if (ft_strcmp(f->type, "burningship") == 0)
		        nb_iter = burning_ship(c, f->c_max_iter);

        - Verificamos se o fractal atualmente selecionado é o Burning Ship.
        - f->type é uma string armazenada dentro da struct t_fractol (por exemplo: "mandelbrot", "julia", "burningship").
        - ft_strcmp(a, b) retorna 0 quando as strings são iguais.

        Logo: se o utilizador pediu para renderizar o burning ship, esta condição é verdadeira.

        São passados dois parâmetros: - c → o ponto complexo atual (coordenada do píxel no plano complexo).
                                      - f->c_max_iter → número máximo de iterações a realizar.

        O retorno (nb_iter) é o escape time → quantas iterações demorou até escapar ou, se não escapou, será c_max_iter.


        1.4.4.3 - burning_ship()

        int	burning_ship(t_complex c, int c_max_iter)
        {
	        t_complex	z;
	        int			nb_iter;

	        nb_iter = 0;
	        z.re = 0;
	        z.im = 0;
	        while (nb_iter < c_max_iter && (z.re * z.re + z.im * z.im) <= 4.0)
	        {
		        z.re = ft_abs(z.re);
		        z.im = ft_abs(z.im);
		        z = c_add(c_mult(z, z), c);
		        nb_iter++;
	        }
	        return (nb_iter);
        }

        A função burning_ship() calcula o escape time de um ponto c (onde c = c_point) no plano complexo.
        O valor devolvido é o número de iterações até a órbita escapar (|z| > 2) ou até atingir o limite máximo (c_max_iter).

        Fórmula iterativa (Burning Ship)

        No Burning Ship, a iteração é igual à do Mandelbrot com uma diferença crucial: antes de elevar ao quadrado, aplicamos o valor
        absoluto às partes real e imaginária do número z  ->   z_{n+1} = (|Re(z_n)| + i·|Im(z_n)|)^2 + c

          - Zn é o valor atual da sequência (número complexo), Representa o estado da órbita na iteração n.
          - c é o parâmetro que estamos a iterar, ele vem do ponto mapeado do pixel (c = c_point).
            Exemplo: se o píxel mapeia para (-0.75, -0.2) então c = -0.75 - 0.2i .
          - z0 é o estado inicial da órbita. COmeça em 0 (z0 = 0).

        Se a sequência (órbita) diverge (|Zn| -> infinito, na prática, se |Zn| > 2 nalguma iteração) o ponto não pertence ao conjunto.
        Se a sequência permanece limitada (|Zn| < 2 para todos as n iterações), o ponto pertence ao conjunto de Burning Ship.

        Assim, o conjunto de BUrning SHip é o conjunto dos parâmetros c para os quais a órbita iniciada em z0 = 0, sob a iteração do 
        burning ship, não escapa.

        







1.4.5 - color = colorize(nb_iter, f);

int	colorize(int iter, t_fractol *f)
{
	if (iter > f->c_max_iter)  // se passarmos o limite
		iter = f->c_max_iter;  // cortamos para o máximo permitido.
	return (f->color_table[iter]);
}

Até aqui: 

    > Já mapeamos um píxel (x, y) para um ponto complexo c_point (função ft_mapping).
    > Calculamos o escape time desse ponto: nb_iter = fractal_escape_time(f, &c_point).
    > Agora falta decidir a cor desse píxel → é exatamente para isso que serve colorize(nb_iter, f).

> color = colorize(nb_iter, f) faz o seguinte:

    - Pega no número de iterações que aquele ponto demorou antes de divergir.
    - Usa esse número como indice na tabela de cores (f->color_table), em que 
      f->color_table[i].
    - Devolve o valor da cor (un int no formato RGB).
    - Essa cor é utilizada na função my_mlx_pixel_put(&f->img, x, y, color) para pintar o pixel no ecrã.

> return (f->color_table[iter])

  Aqui vamos procurar a cor correspondente ao número de iterações.
  f->color_table é um array pré-calculado de cores, criado na função update_color(f): 
  
    f->color_table[i] = polynomial_gradient(i, f->c_max_iter);

  Ou seja: - Se o ponto escapou rápido (por exemplo, iter = 5), a cor virá de color_table[5].
           - Se demorou muito a escapar (por exemplo, iter = 180), vem de color_table[180].
           - Se não escapou (iter == c_max_iter), devolve color_table[c_max_iter], que normalmente é preto 
             (representando o interior do fractal).
             
> Intensidade das cores → o que representam?

  Cada píxel no ecrã corresponde a um ponto c (no Mandelbrot) ou z0 (no Julia).
  Esse ponto é testado → criamos a órbita e contamos quantas iterações demorou até ultrapassar o círculo de escape (|z| > 2).
  Esse número de iterações (iter) é usado para escolher a cor.

  - Caso 1: Ponto divergiu rapidamente

    Isso significa que a órbita escapou em poucas iterações (ex.: iter = 5, ou seja, logo no início |z| > 2).
  
    Na prática, o ponto está longe do conjunto.
    O colorize vai buscar f->color_table[5].

    Normalmente, cores claras, frias ou brilhantes são usadas aqui (ex.: amarelo, azul-claro), porque divergiu muito rápido.

  - Caso 2: Ponto divergiu lentamente

    Isso significa que a órbita demorou muitas iterações antes de escapar (ex.: iter = 180 quando c_max_iter = 200).

    Esses pontos estão perto da fronteira do fractal → é aí que a geometria fractal rica acontece.
    O colorize vai buscar f->color_table[180].

    Normalmente, essas cores são mais escuras, quentes ou densas (ex.: laranja, vermelho, roxo escuro), porque demoram a escapar.
    Estes gradientes de cor criam os anéis coloridos à volta da fronteira.

  - Caso 3: Ponto não divergiu

    Se o ponto nunca escapou, ou seja, iter == f->c_max_iter (o máximo permitido).
    Isso significa que o ponto é considerado interior ao conjunto.
    colorize devolve f->color_table[c_max_iter].

    Tradicionalmente, o interior do Mandelbrot e Julia é pintado de preto.

    Preto representa estabilidade: a órbita nunca fugiu.




1.4.6 - my_mlx_pixel_put(&f->img, x, y, color);

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char *dst;
    int offset;

    if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) // 1) só desenha se (x, y) estiver dentro da imagem
    {
        // 2) Calcula quantos bytes a partir do início do buffer
        //    - y linhas * line_length bytes/linha
        //    - x colunas * bytes_por_pixel
        offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8)); 
        
        dst = img->addr + offset; // 3) dst aponta exatamente para o pixel (x, y) na memória
        
        *(unsigned int *)dst = color; // 4) escreve a cor (4 bytes) nesse endereço
    }
}

Até aqui, no render_fractal:

  - Criamos a imagem fora do ecrã: Criamos uma imagem vazia com mlx_new_image() e obtivemos addr, bpp, line_length, endian através de 
                                   mlx_get_data_addr().
                                   Isto é um framebuffer: um bloco de memória onde vamoss desenhar todos os pixels.

  - Para cada píxel (x,y): Mapeamos (x,y) → ponto complexo c_point (ft_mapping).
                           Calculámos o escape time (nb_iter = fractal_escape_time(f, &c_point)).
                           Convertemos nb_iter em cor (color = colorize(nb_iter, f)).
                          
> A função my_mlx_pixel_put() tem como objetivo escrever a cor de um píxel no sitio certo do framebuffer (a imagem que está na memória).
  Ela pega na cor e escreve-a no endereço exato do pixel (x, y) dentro do framebuffer da imagem, calculando o offset correto a partir da line_lenght 
  (bytes por cada linha) e bites_per_pixel / 8 (bytes por píxel). Depois, na função seguinte, o framebuffer é copiado e mostrado na janela pela MLX
  (mlx_put_image_to_window).

> t_img *img aponta para a struct de imagem (o "framebuffer" onde desenhamos os píxeis na memória, fora do ecrã).
  A t_img representa um framebuffer inicializado/criado pela função mlx_new_image() e que depois foi mapeado/preenchido com a função mlx_get_data_addr(),
  pelo o que:

    - addr passa a apontar para o primeiro byte do framebuffer onde os píxeis estão armazenados, ou seja, aponta para o primeiro byte do primeiro píxel
      da linha 0.
    - bits_per_pixel (bpp) diz-nos quantos bits cada píxel ocupa (normalmente 32 → 4 bytes). Diz-nos quantos bits tem cada píxel, pelo o que cada píxel 
      ocupa bpp / 8 bytes. Dividir por 8 dá-nos os bytes por pixel.
      Ex: 32 → 4 bytes; 24 → 3 bytes ...
    - line_length diz-nos quantos bytes existem por cada linha na imagem. Assim, cada linha ocupa line_length bytes (o que pode ser maior do que WIDTH * (bpp/8)
      porque pode haver padding de alinhamento no fim de cada linha).
    - endian é a ordem com que os bytes são guardados na memória.

  O framebuffer é um bloco contínuo de memória onde cada píxel ocupa, normalmente, 4 bytes.

  typedef struct s_img 
  {
    void *img;            // handle opaco da MLX para a imagem
    char *addr;           // ponteiro p/ o primeiro byte dos píxeis
    int   bits_per_pixel; // bits por píxel (tipicamente 32)
    int   line_length;    // bytes por linha (stride, com possível padding)
    int   endian;         // ordem dos bytes em memória
  } t_img;

  Passamos o ponteiro t_img *img porque a função precisa de ler os metadados (addr, line_length, bpp) para calcular onde escrever o píxel.
  Sem o ponteiro img, a função não saberia: - onde começa a memória dos píxeis (addr);
                                            - quantos bytes tem cada píxel (bits_per_pixel/8);
                                            - quantos bytes ocupa cada linha (line_length, que pode ter padding).


> Como é que a imagem está organizada na memória ?

  A MLX guarda a imagem linha a linha (row-major). Imaginemos o framebuffer como um array de bytes:

  img->addr ──►  [ Linha0 | Linha1 | Linha2 | ... | Linha(HEIGHT-1) ]
                     │         │        │
                     ▼         ▼        ▼
                   bytes     bytes     bytes
                  
  Cada linha ocupa img->line_length bytes (não confundir com o número de píxeis).
  Dentro de cada linha temos os píxeis lado a lado. Cada píxel ocupa bpp/8 bytes consecutivos.

  A imagem é um array de bytes organizado linha a linha:

  addr ─► [ Linha 0:  p0  p1  p2  ...  p(W-1)  PAD ... ]  (line_length bytes)
          [ Linha 1:  p0  p1  p2  ...  p(W-1)  PAD ... ]  (line_length bytes)
          [ Linha 2:  ...                              ]

  Cada píxel p ocupa bpp/8 bytes consecutivos.
  No fim de cada linha pode existir padding (bytes vazios só para alinhamento).

  > O que é “preenchimento linha a linha”?

  Quando desenhamos a imagem, a MLX dá-nos um buffer (um bloco contínuo de memória) onde guardamos todos os píxeis. 
  Esses píxeis estão organizados linha a linha (isto chama-se row-major order):

  Linha 0:  p(0,0)  p(1,0)  p(2,0)  ...  p(W-1,0)  [padding...]
  Linha 1:  p(0,1)  p(1,1)  p(2,1)  ...  p(W-1,1)  [padding...]
  Linha 2:  p(0,2)  p(1,2)  p(2,2)  ...  p(W-1,2)  [padding...]
  ...
  Linha H-1: ...

  - W = WIDTH (nº de colunas), H = HEIGHT (nº de linhas).
  - Cada “p(x,y)” é um píxel; cada píxel ocupa bpp/8 bytes (bits por píxel dividido por 8).
  - No fim de cada linha pode existir padding (bytes extra para alinhamento). Por isso a MLX dá-nos o line_length, ou seja, quantos bytes tem cada linha ao todo, 
    incluindo o padding.

  Preencher linha a linha significa: para y = 0 até H-1, percorremos x = 0 até W-1 e escrevemos a cor de cada píxel no sítio certo do buffer. 
                                     É o que o duplo while faz no render_fractal().
  
  Para saltar de linha, NUNCA devemos utilizar WIDTH * (bpp/8), porque pode haver padding no fim de cada linha (para alinhamento da memória). 
  A MLX garante o valor correto de line_length; temos de usá-lo para saltarmos linha a linha sem nos perdermos. line_length é o que nos mantém
  sempre alinhados na memória certa.
      

> if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)

  Evita escrever fora dos limites da imagem.
  Só desenha se o píxel (x, y) estiver dentro do rentângulo [0..WIDTH-1] x [0..HEIGHT-1].

  
> Cálculo do endereço do píxel: offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));

  O objetivo aqui é converter a coordenada do píxel (x, y) num deslocamento (offset), em bytes, dentro do framebuffer (img->addr), a partir do inicio,
  para então escrevermos a cor nesse sitio correto. Sem este cálculo não saberiamos onde escrever a cor.

  - img->line_length → quantos bytes há em cada linha de pixels (atenção: pode ter padding, ou seja, pode ser maior do que WIDTH * (bpp/8)).
  - img->bits_per_pixel / 8 → quantos bytes por píxel (normalmente 4 num MLX clássico: 32 bpp).

  A imagem é guardada linha a linha. Para chegar ao píxel (x, y): - salto vertical: ir até à linha y -> y * line_length bytes
                                                                  - salto horizontal: ir até à coluna x -> x * (bpp/8) bytes

  > Salto vertical (nas linhas): y * img->line_length

    Corresponde ao “salto”, em bytes, do início do buffer até ao início da linha y.
    Se cada linha fecha com line_length bytes, então, depois de y linhas, percorremos y * line_length bytes.

    Pensemos no buffer como várias “prateleiras” (linhas). Para chegarmos à linha y, damos um salto de y * line_length bytes:

    addr ──► |<── line_length ──>|<── line_length ──>|<── line_length ──>|
          Linha 0             Linha 1               ...      Linha y


  > Salto horizontal (das colunas dentro da mesma linha): x * (img->bits_per_pixel / 8)

    Uma vez estarmos numa determinada linha y, percorremos as colunas até à coluna x.
    Cada coluna/pixel consome bpp/8 bytes:

    Início da linha y
    │
    ├─ + 0*(bpp/8)  → p(0,y)
    ├─ + 1*(bpp/8)  → p(1,y)
    ├─ + 2*(bpp/8)  → p(2,y)
    └─ + x*(bpp/8)  → p(x,y)

    - img->bits_per_pixel / 8 é “quantos bytes por píxel”: se bpp = 32, então 32 / 8 = 4 bytes por píxel.

  > Somando: offset = (y * img->line_length) + (x * (img->bits_per_pixel / 8));

    O offset é o deslocamento em bytes até ao píxel (x, y) dentro do buffer:

      - "y * line_length” leva-nos ao início da linha y; 
      - "x * (bpp/8)” avança x píxeis nessa linha.
      - Somando, obtemos o deslocamento total até (x, y) que representa o endereço certo para escrever a cor.

> Ponteiro para o pixel: dst = img->addr + offset;

    - img->addr → ponteiro para o início do buffer da imagem - o primeiro byte do framebuffer (foi obtido por mlx_get_data_addr()).
    - offset: é o deslocamento em bytes desde o ínicio do framebuffer (img->addr) até ao pixel (x, y) que queremos pintar.
              Foi calculado na linha anterior.

  Aqui, vamos pegar no endereço base (img->addr) e avançar offset bytes. O resultado é um ponteiro (que é o dst) para o primeiro byte do pixel (x, y).
  Assim, dst aponta exatamente para o ínicio do pixel (x, y) na memória.

  
> Escrita da cor: *(unsigned int *)dst = color;

    - dst é um ponteiro para o endereço certo do píxel na memória. Ele aponta para o primeiro byte do pixel (x, y): dst = img->addr + offset; 
    - Depois ele escreve 4 bytes (32 bits), de uma vez só, nessa posição da memória com o valor de color -> *(unsigned int *)dst = color;
      Converte dst para unsigned int* e escreve 4 bytes (o píxel inteiro), assumindo 32 bpp.
  
      Porquê unsigned int? Porque com 32 bits = 4 bytes conseguimos englobar RGB(A) num único pixel inteiro. 
                            Escrever 4 bytes de uma vez é simples e rápido.

  - offset corresponde a quantos bytes temos de andar desde o ínicio do buffer (img->addr) até ao píxel (x, y).

  O que é o int color? É a cor que queremos colocar no píxel (x, y).
                       Ela vem da função colorize(), que vai buscar uma cor à tabela f->color_table[nb_iter].

  Detalhe: a “ordem” com que a cor aparece no ecrã depende do endianness (e do backend da MLX). 
  No Linux/X11 clássico, escrever um unsigned int coloca na memória os bytes em ordem B, G, R, A quando endian == 0 (little-endian). 
  Se as cores saem “trocadas”, este é o motivo.



  Depois de concluido o loop da função render_fractal() e de todos os pixeis terem sido pintados no seu devido lugar, no framebuffer, vamos ver 
  como vamos colocar esssa imagem na janela:

  mlx_put_image_to_window(f->mlx, f->win, f->img.img, 0, 0);

  A função mlx_put_image_to_window() faz uma cópia da imagem MLX, que acabamos de pintar, para a janela vísivel, no ecrã.

  Ela recebe:

    > f->mlx: é o handle/contexto gráfico da MLX (ligação ao sistema gráfico).
    > f->win: é a janela de destino onde queremos mostrar a imagem (handle criado por mlx_new_window).
    > f->img.img: é o handle da imagem MLX (criada por mlx_new_image) que contém o framebuffer que preenchemos píxel a píxel.
                  O buffer de píxeis (onde escrevemos as cores) é f->img.addr.
                  O objeto imagem usado pela MLX para comunicar com o servidor gráfico é f->img.img.
    > 0, 0: são as coordenadas na janela onde a imagem será desenhada (offset do canto superior esquerdo).
            (0,0) → situa-se no topo-esquerda.
            Por exemplo, se passarmos (50, 30), a imagem aparece deslocada 50 px à direita e 30 px para baixo.
            Qualquer parte que “saia” da janela é recortada (clipping).


            
1.5 - mlx_key_hook(f.win, (int (*)())(void *)handle_key, &f);

  1.5.1 - handle_key()

  int	handle_key(int keycode, t_fractol *f)
  {
	  if (keycode == KEY_ESC)
		  exit_fractol(QUIT, f);
	  else if (keycode == KEY_W || keycode == KEY_UP)
		  f->offset_y -= 0.4 * f->zoom;
	  else if (keycode == KEY_A || keycode == KEY_LEFT)
		  f->offset_x -= 0.4 * f->zoom;
	  else if (keycode == KEY_S || keycode == KEY_DOWN)
		  f->offset_y += 0.4 * f->zoom;
	  else if (keycode == KEY_D || keycode == KEY_RIGHT)
		  f->offset_x += 0.4 * f->zoom;
    handle_fractal_keys(keycode, f);  (1.5.1.1)
    handle_key_iterations(keycode, f);  (1.5.1.2)
	  handle_key_suite(keycode, f);  (1.5.1.3)
	  render_fractal(f);
	  return (0);
  }

  A função mlx_key_hook() é um atalho da MLX para dizer: "Nesta janela win, quando houver um evento KeyPress (tecla premida), chama a função callback (handle_key), passando também o valor
  f ao callback".
  Ou seja, mlx_key_hook() é o registo de um callback para o evento do teclado.
  A funçãom à partida só vai registar o callback, e o código segue o fluxo normalmente para as linhas seguintes.
  Só depois quando entrarmos na função mlx_loop() é que a MLX começa a escutar os eventos e a chamar o callback da mlx_key_hook() quando pressionamos uma tecla, na janela.
  Até chamarmos a função mlx_loop(), nenhuma callback de evento (teclado/rato/fechar janela) será chamado.

  O f.win é o handle da janela que criamos com a função mlx_new_window().
  A janela foi criada com as dimensões definidas no header file e com o título f->type.
  É nesta janela que mostramos a imagem com mlx_put_image_to_window().
  Nós passamos este handle como forma de dizer à MLX qual a janela deve ouvir os eventos e onde desenhar.

  Porquê que passamos &f ?

  &f é o endereço da variável f (do tipo t_fractol) - é um ponteiro para o estado do programa Fract-ol.
  A MLX vai guardar esse ponteiro e, quando chamar a função callback (handle_key), passa como segundo argumento: handle_key(keycode, (t_fractol *)param); // param == &f

  Até ao momento, f já tem:

    > Contextos MLX: - f->mlx → contexto/ligação à MLX (Display* em X11).
                     - f->win → handle da janela (onde ouve eventos/desenha).
                     - f->img → a imagem/framebuffer atual: - img (handle MLX da imagem),
                                                            - addr (ponteiro para os bytes dos píxeis),
                                                            - bits_per_pixel, line_length, endian.
                                                            
    > Parâmetros do render: - f->type → "mandelbrot", "julia", "burningship", "phoenix".
                            - f->c_max_iter → máximo de iterações (precisão).
                            - f->zoom → escala da vista.
                            - f->offset_x, f->offset_y → “pan” (centro da câmara no plano complexo).
                            - f->color_mode e f->color_table → modo/paleta de cores.

  Passar &f (e não uma cópia) é fundamental para: - Ler e alterar o mesmo estado (zoom, offset, iterações, tipo, cores) dentro do callback.
                                                  - Re-renderizar de imediato com render_fractal(f) já atualizado.
  
  > Eventos: coisas que acontecem no sistema das janelas: tecla premida/solta, movimento/scroll do rato, redimensionar, fechar a janela, etc.
  > Hook: é um registo de callback (função) para um determinado evento. Tu dizes à MLX: “Quando acontecer X nesta janela, chama esta função com estes parâmetros”.
  > Escuta (listening): quando entramos na função mlx_loop(), a MLX fica a bloquear e espera os eventos. Quando um evento chega, 
                        verifica os hooks registados e invoca o callback correspondente. É literalmente a “escuta” do programa às ações do utilizador e do SO.

  A função mlx_key_hook(f.win, (int (*)())(void *)handle_key, &f), faz o registo do callback da tecla premida (do key hook) para a janela f.win.
  
    - f.win: a janela onde vai “ouvir” as teclas.
    - handle_key: a função que deve ser chamada quando uma tecla é premida.
    - &f: um ponteiro que a MLX te devolve como segundo argumento do callback (o “contexto”/estado).

  [Teclado]--scan code--> envia o evento -> [SO] -> (KeyPress para janela (f->win)) ->[Fila de Eventos do SO] ->(mlx_loop lê o evento)
                                                                                                                          |
                                                                                                                          v
          atualiza estado (offset/iter/...)  <- chama handle_key(keycode, &f) <-  (há hook para KeyPress?) <- [Despacho MLX para f.win]
                    |
                    v
            render_fractal(f)      -------> [Janela atualizada no ecrã] -> volta ao mlx_loop
     (preenche framebuffer + put_image)

  Re-renderização da cena

  Depois de mudar o estado, o handle_key chama render_fractal(f): - se já houver uma imagem anterior, destrói-a (no teu fluxo atual).
                                                                  - cria uma imagem MLX nova (mlx_new_image) e obtém o buffer de píxeis (mlx_get_data_addr).
                                                                  - percorre a grelha de píxeis (x,y); para cada píxel faz o mapeamento para o plano complexo,
                                                                    usando o zoom e o offset atualizados (a “câmara”); calcula o escape time consoante o fractal;
                                                                    transforma o número de iterações numa cor usando a paleta (color_table); escreve essa cor no 
                                                                    buffer (píxel-a-píxel) com my_mlx_pixel_put.
                                                                  - No fim, copia a imagem para a janela com a função mlx_put_image_to_window().
                                                                  
  O handle_key() retorna, a MLX volta ao mlx_loop e fica à espera do próximo evento.


  
            
1.6 - mlx_mouse_hook(f.win, (int (*)())(void *)handle_mouse_key, &f); 

void	handle_mouse_key(int keycode, int x, int y, t_fractol *f)
{
	(void)x;
	if (keycode == MOUSE_WHEEL_UP)
		zoom_at_point(x, y, 0.8, f);  (1.6.1)
	else if (keycode == MOUSE_WHEEL_DOWN)
		zoom_at_point(x, y, 1.2, f);  (1.6.1)
	render_fractal(f);
}


1.6.1 - zoom_at_point()

void	zoom_at_point(int x, int y, double zoom_factor, t_fractol *f)
{
	double	scale_x = (4.0 / WIDTH)  * f->zoom;
	double	scale_y = (4.0 / HEIGHT) * f->zoom;

	// (A) Converte o pixel do cursor (x,y) para o ponto complexo sob o rato:
	double	mouse_re = (x - WIDTH  / 2) * scale_x + f->offset_x;  // <<--
	double	mouse_im = (y - HEIGHT / 2) * scale_y + f->offset_y;  // <<--

	// (B) Aplica o novo zoom:
	f->zoom *= zoom_factor;

	// (C) Reposiciona os offsets para manter (mouse_re,mouse_im) no MESMO pixel:
	f->offset_x = mouse_re - (mouse_re - f->offset_x) * zoom_factor; // <<--
	f->offset_y = mouse_im - (mouse_im - f->offset_y) * zoom_factor; // <<--
}

1) O hook do rato passa as coordenadas do cursor

  O mlx_mouse_hook dá-te as coordenadas do cursor (x, y) no momento do scroll - e transmitimos essas coordenadas para a função zoom_at_point().
  Ou seja, o mlx_mouse_hook chama handle_mouse_key com o (x,y) do cursor no momento do scroll. Passamos esse (x,y) para zoom_at_point(...).

2) zoom_at_point ancora o ponto debaixo do cursor

  (A) Calculamos o ponto do plano complexo que está exatamente debaixo do cursor antes de mudar o zoom (mouse_re, mouse_im).
  (B) Mudamos o f->zoom.
  (C) Ajustamos offset_x e offset_y com aquela fórmula para que, depois do zoom, o mesmo píxel (x,y) continue a mapear para o mesmo ponto complexo
     (mouse_re,mouse_im).

  Resultado: o zoom “segue” o cursor em qualquer sítio do ecrã.

  As linhas que calculam mouse_re/mouse_im usam as coordenadas do cursor para descobrir que ponto do plano complexo está debaixo dele.
  Depois do f->zoom *= zoom_factor, as fórmulas dos offsets reposicionam o centro (offsets) de modo que aquele mesmo ponto do plano (o mouse_re, mouse_im) 
  continue exatamente debaixo do cursor após o zoom.

  offset_x' = mouse_re - (mouse_re - offset_x) * zoom_factor
  offset_y' = mouse_im - (mouse_im - offset_y) * zoom_factor

3) Renderização imediata

  Depois, render_fractal(f); recompõe a imagem com o novo zoom e os novos offsets, e faz mlx_put_image_to_window(...).

É isso que faz com que, ao fazermos zoom em qualquer parte do ecrã, a vista “siga” o ponteiro: tu fixas (ancoras) o ponto sob o cursor antes do zoom e ajustas os offsets para que ele não se mexa no ecrã depois do zoom.






1.7 - mlx_hook(f.win, 17, 0, (int (*)())(void *)handle_close, &f);

void	handle_close(t_fractol *f)
{
	(void)f;
	exit_fractol(0, f);
}

1.8 - mlx_loop(f.mlx); 