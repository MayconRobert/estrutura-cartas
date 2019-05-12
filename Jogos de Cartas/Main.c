// Inclui o Allegro 5
#include <allegro5/allegro.h>
// Inclui o cabeçalho do add-on para uso de imagens
#include <allegro5/allegro_image.h>
//Inclui  as mensagens Allegro
#include <allegro5/allegro_native_dialog.h>


// Função Main
int main(void)
{
	// Variável representando a janela principal
	ALLEGRO_DISPLAY *janela = NULL;

	// Variável representando a imagem
	ALLEGRO_BITMAP *imagem = NULL;

	// Inicializa a biblioteca do Allegro
	al_init();
	
	//Tenta inicializar o Allegro
	if (!al_init()) {
		al_show_native_message_box(janela, "Error", "Erro", "Falha ao inicializar o Allegro!",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		return 0;
	}

	// Inicializa o add-on para utilização de imagens
	al_init_image_addon();

	// Cria a janela. Largura X Altura
	janela = al_create_display(1024, 768);

	// Carrega a imagem de fundo
	imagem = al_load_bitmap("../background.jpg");

	//Checa se a imagem carregou corretamente
	if (!imagem) {
		al_show_native_message_box(janela, "Error", "Erro", "Falaha ao carregar a imagem",
			NULL, ALLEGRO_MESSAGEBOX_ERROR);
		al_destroy_display(janela);
		return 0;
	}

	// Desenha a imagem na tela. Os valores representam a distância das bordas da imagem na tela
	al_draw_bitmap(imagem, 0, 0, 0);

	// Atualiza a tela
	al_flip_display();

	// Segura a execução por 10 segundos
	al_rest(10.0);

	// Finaliza a janela
	al_destroy_display(janela);

	// Libera a memória da imagem
	al_destroy_bitmap(imagem);

	return 0;
}