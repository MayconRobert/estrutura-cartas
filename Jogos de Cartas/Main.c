// Inclui o Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
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

// Função Main
int main(void)
{
	/*----------------------VARIÁVEIS DO PROGRAMA-----------------------*/
	// Janela principal
	ALLEGRO_DISPLAY *janela = NULL;

	// Imagens
	ALLEGRO_BITMAP *background = NULL;
	ALLEGRO_BITMAP *btnJogar = NULL;
	ALLEGRO_BITMAP *btnLeader = NULL;
	ALLEGRO_BITMAP *btnComoJogar = NULL;
	ALLEGRO_BITMAP *btn21 = NULL;
	ALLEGRO_BITMAP *btnTrunfo = NULL;
	ALLEGRO_BITMAP *btnMenu = NULL;

	// Fila de eventos na tela
	ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;

	// Recebe os eventos que sai da fila de eventos
	ALLEGRO_EVENT evento;

	// Controla quanto tempo será esperado para acontecer um evento até que continue a execução
	ALLEGRO_TIMEOUT timeout;

	// Arquivo de fonte
	ALLEGRO_FONT *fonte = NULL;

	// Controla a saida do programa
	int sair = 0;

	// Inicializa o timeout com um tempo de 50ms
	al_init_timeout(&timeout, 0.05);

	/*----------------------INICIALIZA O PROGRAMA-----------------------*/
	
	// Tenta inicializar o Allegro
	if (!al_init()) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o Allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Tenta inicializar o add-on para utilização de imagens
	if (!al_init_image_addon()) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o add-on de Imagens!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Tenta inicializar o add-on para utilização de fontes
	if (!al_init_font_addon()) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o add-on de Fontes!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Inicialização do add-on para uso de fontes True Type
	if (!al_init_ttf_addon())
	{
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o add-on de Fontes True Type!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return -1;
	}

	// Ativa a utilização do mouse
	if (!al_install_mouse())
	{
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao habilitar o mouse",
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

	// Atribui o cursor padrão do sistema para ser usado
	if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
	{
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao atribuir o cursor do mouse",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(janela);
		return -1;
	}

	// Carrega a imagem de fundo
	background = al_load_bitmap("../background.jpg");
	btnJogar = al_load_bitmap("../btnJogar.jpg");
	btnComoJogar = al_load_bitmap("../btnComoJogar.jpg");
	btnLeader = al_load_bitmap("../btnLeaderboards.jpg");

	// Checa se a imagem carregou corretamente
	if (!background || !btnJogar || !btnComoJogar || !btnLeader) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao carregar as imagens",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_bitmap(background);
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

	// Configura o título da janela
	al_set_window_title(janela, "JOGOS DE CARTAS");

	// Registra todos os eventos ocorridos na janela para a fila de eventos
	al_register_event_source(fila_eventos, al_get_display_event_source(janela));

	// Irá ser tratado os eventos vindos do mouse
	al_register_event_source(fila_eventos, al_get_mouse_event_source());

	// Desenha as imagens na tela. Os valores representam o X e Y e o ultimo é uma flag
	al_draw_bitmap(background, 0, 0, 0);
	al_draw_bitmap(btnJogar, 320, 300, 0);
	al_draw_bitmap(btnComoJogar, 320, 400, 0);
	al_draw_bitmap(btnLeader, 320, 500, 0);

	// Texto estático centralizado
	// Parametros: fonte, cor, posição X, posição Y, flags, texto
	al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 90, ALLEGRO_ALIGN_CENTRE, "JOGOS DE CARTAS");

	// Atualiza a tela
	al_flip_display();

	/*----------------------EXECUÇÃO DO PROGRAMA-----------------------*/
	
	// Permanece no Loop até que usuário clique no "X"
	while (!sair)
	{
		// Verifica se há eventos na fila
		while (!al_is_event_queue_empty(fila_eventos))
		{
			
			/*
			A seguinte função verifica na fila de eventos (primeiro parametro) durante o tempo especificado no timeout (terceiro parametro)
			se há algum evento. Caso não haja retorna 0, caso contrário retira o primeiro evento da fila e armazena na variável de
			evento (segundo parametro) em seguida retorna 1
			*/
			al_wait_for_event_until(fila_eventos, &evento, &timeout);

			// Checa se é do tipo de fechar
			if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			{
				sair = 1;
			}
			// Checa se é do tipo de click
			else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {

				// Checa se o click foi no primeiro botão
				if (evento.mouse.x >= LARGURA_TELA / 2 - al_get_bitmap_width(btnJogar) / 2 &&
					evento.mouse.x <= LARGURA_TELA / 2 + al_get_bitmap_width(btnJogar) / 2 &&
					evento.mouse.y >= ALTURA_TELA / 2 - al_get_bitmap_height(btnJogar) &&
					evento.mouse.y <= ALTURA_TELA / 2 + al_get_bitmap_height(btnJogar) - 90)
				{
					al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_QUESTION);

					// Libera os botões
					al_destroy_bitmap(btnJogar);
					al_destroy_bitmap(btnComoJogar);
					al_destroy_bitmap(btnLeader);

					// Desenha novamente a tela
					al_draw_bitmap(background, 0, 0, 0);

					// Adiciona novamente o titulo
					al_draw_text(fonte, al_map_rgb(0, 0, 255), LARGURA_TELA / 2, 90, ALLEGRO_ALIGN_CENTRE, "JOGOS DE CARTAS");

					// Adiciona os novos botões
					btn21 = al_load_bitmap("../btn21.jpg");
					btnTrunfo = al_load_bitmap("../btnTrunfo.jpg");
					btnMenu = al_load_bitmap("../btnMenu.jpg");

					// Checa se a imagem carregou corretamente
					if (!btn21 || !btnTrunfo || !btnMenu) {
						al_show_native_message_box(janela, "Error", "Erro", "Falha ao carregar as imagens",
							NULL, ALLEGRO_MESSAGEBOX_ERROR);
						al_destroy_bitmap(background);
						return -1;
					}

					// Desenha os botões na tela
					al_draw_bitmap(btn21, 320, 300, 0);
					al_draw_bitmap(btnTrunfo, 320, 400, 0);
					al_draw_bitmap(btnMenu, 600, 650, 0);

					al_flip_display();

				}

				// Checa se o click foi no segundo botão
				else if (evento.mouse.x >= LARGURA_TELA / 2 - al_get_bitmap_width(btnComoJogar) / 2 &&
						evento.mouse.x <= LARGURA_TELA / 2 + al_get_bitmap_width(btnComoJogar) / 2 &&
						evento.mouse.y >= ALTURA_TELA / 2 - al_get_bitmap_height(btnComoJogar) + 110 &&
						evento.mouse.y <= ALTURA_TELA / 2 + al_get_bitmap_height(btnComoJogar) + 10)
					 {
						al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_BUSY);
					 }

				// Checa se o click foi no terceiro botão
				else if (evento.mouse.x >= LARGURA_TELA / 2 - al_get_bitmap_width(btnComoJogar) / 2 &&
					evento.mouse.x <= LARGURA_TELA / 2 + al_get_bitmap_width(btnComoJogar) / 2 &&
					evento.mouse.y >= ALTURA_TELA / 2 - al_get_bitmap_height(btnComoJogar) + 200 &&
					evento.mouse.y <= ALTURA_TELA / 2 + al_get_bitmap_height(btnComoJogar) + 120 )
				{
					al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_MOVE);
				}

				else {
					al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT);
				}
			}
		}
	}

	// Libera a memória da janela
	al_destroy_display(janela);

	// Libera a memória do background
	al_destroy_bitmap(background);

	// Libera a memória da fila de eventos
	al_destroy_event_queue(fila_eventos);

	// Libera a memória da fonte
	al_destroy_font(fonte);

	return 0;
}