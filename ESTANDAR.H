extern "C"
{
  void  video_tipo();
  void  tipo_cursor(int );
  void  datos_a_puerta(unsigned int ,unsigned char ,unsigned char ,unsigned char ,unsigned char ,unsigned char );
  int  datos_de_puerta(unsigned int );
  int  punto_medio(int );
  void  leer_fecha(char * );
  void  leer_hora(char * );
  void  actualizar_fecha(char * );
  void  actualizar_hora(char * );
  int  create_file(char * );
  int  open_file(char *,int );
  int  close_file(int);
  int  delete_file(char * );
  int  read_file(int ,int ,void * );
  int  write_file(int ,int ,void * );
  void  seek_file(int ,long int ,int );
  short  recibe_un_dato(char *,short ,short ,int ,int ,int ,int ,int );
  void  v_save(unsigned int ,unsigned int ,unsigned int ,unsigned int);
  void  v_load(unsigned int ,unsigned int ,unsigned int ,unsigned int);
  void  v_window(unsigned int ,unsigned int ,unsigned int ,unsigned int ,unsigned int ,unsigned int);
  void  v_borde(unsigned int ,unsigned int ,unsigned int ,unsigned int ,unsigned int);
  void  v_write(unsigned int ,unsigned int ,char *,unsigned char);
  void  despliegue(int ,int ,int ,int ,int ,int ,int ,int );
  void  s_copy(char * ,char * );
  int  s_comp(char * ,char * );
  int  s_leng(char * );
  void  dead_time(unsigned int);
  void  video_pos();
  int  keypressed();
  void  block(int ,int );
  unsigned char  recibir(int );
  void  enviar(int ,char );
}