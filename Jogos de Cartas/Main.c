// Inclui o Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabe�alho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
// Inclui  as mensagens Allegro
#include <allegro5/allegro_native_dialog.h>
// Inclui fun'c~oes gerais para Texto
#include <allegro5/allegro_font.h>
// Fontes True Type
#include <allegro5/allegro_ttf.h>
#include <stdio.h>

#define LARGURA_TELA 1024
#define ALTURA_TELA 768

// Fun��o Main
int main(void)
{
	/*----------------------VARI�VEIS DO PROGRAMA-----------------------*/
	// Janela principal
	ALLEGRO_DISPLAY *janela = NULL;

	// Imagem de fundo
	ALLEGRO_BITMAP *imagem = NULL;

	// Fila de eventos na tela
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

	// Recebe os eventos que sai da fila de eventos
	ALLEGRO_EVENT evento;

	// Controla quanto tempo ser� esperado para acontecer um evento at� que continue a execu��o
	ALLEGRO_TIMEOUT timeout;

	// Arquivo de fonte
	ALLEGRO_FONT *fonte = NULL;

	// Inicializa o timeout com um tempo de 50ms
	al_init_timeout(&timeout, 0.05);

	/*----------------------INICIALIZA O PROGRAMA-----------------------*/
	
	// Tenta inicializar o Allegro
	if (!al_init()) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o Allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Tenta inicializar o add-on para utiliza��o de imagens
	if (!al_init_image_addon()) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o add-on de Imagens!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Tenta inicializar o add-on para utiliza��o de fontes
	if (!al_init_font_addon()) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o add-on de Fontes!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Inicializa��o do add-on para uso de fontes True Type
	if (!al_init_ttf_addon())
	{
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o add-on de Fontes True Type!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Cria a janela
	janela = al_create_display(LARGURA_TELA, ALTURA_TELA);

	// Checa se criou a janela
	if (!janela) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao criar a janela!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(janela);
		return -1;
	}

	// Carrega a imagem de fundo
	imagem = al_load_bitmap("../background.jpg");

	// Checa se a imagem carregou corretamente
	if (!imagem) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao carregar a imagem",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_bitmap(imagem);
		return -1;
	}

	// Carrega o arquivo de fonte
	// Parametros: fonte, tamanho, flags
	fonte = al_load_font("../CASTELAR.TTF", 48, 0);
	if (!fonte)
	{
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao carregar a Fonte",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(janela);
		return -1;
	}

	// Inicializa a fila de eventos
	fila_eventos = al_create_event_queue();

	// Checa se a fila de eventos foi criada corretamente
	if (!fila_eventos) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao criar a fila de eventos da tela",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_event_queue(fila_eventos);
	}

	// Configura o t�tulo da janela
	al_set_window_title(janela, "JOGOS DE CARTAS");

	// Registra todos os eventos ocorridos na janela para a fila de eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	// Desenha a imagem na tela. Os valores representam a dist�ncia das bordas da imagem na tela
	al_draw_bitmap(imagem, 0, 0, 0);

	// Texto est�tico centralizado
	// Parametros: fonte, cor, posi��o X, posi��o Y, flags, texto
	al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 90, ALLEGRO_ALIGN_CENTRE, "JOGOS DE CARTAS");

	// Atualiza a tela
	al_flip_display();

	/*----------------------EXECU��O DO PROGRAMA-----------------------*/
	
	// Permanece no Loop at� que usu�rio clique no "X"
	while (1)
	{

		/* 
		A seguinte fun��o verifica na fila de eventos (primeiro parametro) durante o tempo especificado no timeout (terceiro parametro)
		se h� algum evento. Caso n�o haja retorna 0, caso contr�rio retira o primeiro evento da fila e armazena na vari�vel de 
		evento (segundo parametro) em seguida retorna 1
		*/
		int tem_eventos = al_wait_for_event_until(fila_eventos, &evento, &timeout);

		// Checa se tem eventos e se � do tipo de fechar
		if (tem_eventos && evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			break;
		}
		
	}

	// Libera a mem�ria da janela
	al_destroy_display(janela);

	// Libera a mem�ria da imagem
	al_destroy_bitmap(imagem);

	// Libera a mem�ria da fila de eventos
	al_destroy_event_queue(fila_eventos);

	// Libera a mem�ria da fonte
	al_destroy_font(fonte);

	return 0;
}