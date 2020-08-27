typedef struct Airplane{
    int id;
    struct Airplane * next;
}airplane;

/*Function Declaration*/
void plane_add(airplane * flight101, int number);
int length(airplane * flight101);
int plane_delete(airplane ** flight101);
void airport();