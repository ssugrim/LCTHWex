#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

/* Extra credit 2 - In this case I'm taking both the db size and the lengths
 * of the fields as arguments. I'll make 3 heap allocs, one for the 
 * struct Address, one for names, and one for e-mails. I'll then patch
 * up the pointers to point to the correct types. This avoids having to 
 * manually calculate offest and using void pointers. 
 *
 */

/*
 * The basic atom of data. Multiples of these will be stored in the Larger 
 * Database.
 */
struct Address{
    int id;
    int set;
    char *name; // I'll have to loop through this array, pointing each of these
    char *email;
};

/*
 * This is the database. When created it will have size populated. 
 * When stored we write size as the first binary chunk of the file
 */
struct Database {
    int size;
    int max_len;
    struct Address * rows;
    char *names;
    char *emails;
};

/*
 * The connection is baiscally just a tieing element. It gets passed around
 * to reference the Data structure in memory and the file descriptor on disk
 */
struct Connection {
    FILE *file;
    struct Database *db;
};

/*
 * die forward declaration
 */
void die(const char *message, struct Connection *conn);

/*
 * In a real program this would do "actual work"
 */

void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

/*
 * "Opens" the db and loads the file into memory, open and close
 * are now the primary managers of memory
 */
struct Connection *Database_open(const char *filename)
{
    //make a Conn object 
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die ("Memory error",NULL);

    //open the file
    conn->file = fopen(filename, "r+");
    if(!conn->file) die("Failed to open the file",conn);

    //make a DB object
    conn->db = malloc(sizeof(struct Database));

    //Read the size of the db
    int rc = fread(&conn->db->size, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to read database size.",conn);

    //Read the max_len of the db
    rc = fread(&conn->db->max_len, sizeof(int), 1, conn->file);
    if(rc != 1) die("Failed to read database size.",conn);

    //Read the Address Array
    conn->db->rows = malloc(conn->db->size * sizeof(struct Address)); 
    if(!conn->db) die("Could not allocate addr array.",conn);
    rc = fread(conn->db->rows, sizeof(struct Address), 
            conn->db->size, conn->file);
    if(rc != conn->db->size) die("Failed to load add array.",conn);

    //Read the Names Array
    conn->db->names = malloc(conn->db->size * conn->db->max_len); 
    if(!conn->db) die("Could not allocate names array.",conn);
    rc = fread(conn->db->names, conn->db->max_len, 
            conn->db->size, conn->file);
    if(rc != conn->db->size) die("Failed to load names array.",conn);

    //Read the emails Array
    conn->db->emails = malloc(conn->db->size * conn->db->max_len); 
    if(!conn->db) die("Could not allocate emails array.",conn);
    rc = fread(conn->db->emails, conn->db->max_len, 
            conn->db->size, conn->file);
    if(rc != conn->db->size) die("Failed to load emails array.",conn);

    //Fix all the name,email pointers in the address's
    int i = 0;
    for (i = 0; i < conn->db->size; i++){
        conn->db->rows[i].name = conn->db->names + (i * conn->db->max_len);
        conn->db->rows[i].email = conn->db->emails + (i * conn->db->max_len);
    }

    printf("The db contains %d records of lenth %d \n", 
            conn->db->size,conn->db->max_len);
    return conn;
}

/*
 * Cleaing up function, all memeory that is allocated is release here
 * either from open or create.
 */
void Database_close(struct Connection *conn)
{
    if(conn) {
        if(conn->file) fclose(conn->file); // Close the file if it was opened
        if(conn->db->rows) free(conn->db->rows);
        if(conn->db->names) free(conn->db->names);
        if(conn->db->emails) free(conn->db->emails);
        if(conn->db) free(conn->db); //Deallocate the DB memeory chunk
        free(conn); //Deallocate the tie (RIAA should make this cleaner)
    }
}

/*
 * Commit memory changes to disk
 */
void Database_write(struct Connection *conn)
{
    //move file pointer back to origin
    rewind(conn->file); 

    //Write the size value into the file 
    int rc = fwrite(&conn->db->size, sizeof(int), 1, conn->file); 
    if (rc != 1) die("Failed to write database size ",conn);

    //Write the max_len value into the file 
    rc = fwrite(&conn->db->max_len, sizeof(int), 1, conn->file); 
    if (rc != 1) die("Failed to write database max_len ",conn);

    //write the address array
    rc = fwrite(conn->db->rows, sizeof(struct Address), conn->db->size, conn->file); 
    if (rc != conn->db->size) die("Failed to write address array.",conn);

    //write the names array
    rc = fwrite(conn->db->names, conn->db->max_len, conn->db->size, conn->file); 
    if (rc != conn->db->size) die("Failed to write names array.",conn);

    //write the names array
    rc = fwrite(conn->db->emails, conn->db->max_len, conn->db->size, conn->file); 
    if (rc != conn->db->size) die("Failed to write emails array.",conn);

    //flush write buffers (in the case of bufferd IO)
    rc = fflush(conn->file);
    if(rc == -1) die("Cannot flush database.",conn);
}

/*
 * Creates a db object of apropriate size
 */

struct Connection *Database_create(char *filename, int size, int max_len)
{
    //make a Conn object 
    struct Connection *conn = malloc(sizeof(struct Connection));
    if(!conn) die ("Memory error",NULL);
    
    //open the file
    conn->file = fopen(filename, "w");
    if(!conn->file) die("Failed to open the file",conn);

    //make a DB object
    conn->db = malloc(sizeof(struct Database));

    //set db size
    conn->db->size = size;

    //set db max_len
    conn->db->max_len = max_len;

    //Create an zerored Address array of the right size 
    conn->db->rows = calloc(size, sizeof(struct Address)); 
    conn->db->names = calloc(size, max_len); 
    conn->db->emails = calloc(size, max_len); 

    //Technically this is unecissary at this point but I'm making a protoype
    //TODO Are these assignments safe?
    int i = 0;
    for (i = 0; i < size; i++){
        conn->db->rows[i].id = i;
        conn->db->rows[i].name = conn->db->names + (i * max_len);
        conn->db->rows[i].email = conn->db->emails + (i * max_len);
    }

    printf("Creating a database for %d records of length %d\n",size,max_len);

    return conn;
}

/*
 * Actually set one of the database entries to something non-zero
 */
void Database_set(struct Connection *conn, int id, const char *name, 
        const char *email)
{
    //TODO this might need to change to deal with the new structure
    //this will get a pointer to the struct Address in the array at id.
    struct Address *addr = &conn->db->rows[id]; 
    if(addr->set) die("Already set, delete it first",conn);

    addr->set = 1;
    //WARNING: bug, read the "How to break it" and fix this
    char *res = strncpy(addr->name, name, conn->db->max_len);
    //demonstrate the strncpy bug
    if(!res) die("Name copy failed",conn);

    res = strncpy(addr->email, email, conn->db->max_len);
    if(!res) die("Email copy filed",conn);
}

/*
 *Get basically prints the record
 */
void Database_get(struct Connection *conn, int id)
{
    //TODO this might need to change to deal with the new structure
    struct Address *addr = &conn->db->rows[id];

    if(addr->set){
        Address_print(addr);
    } else{
        die("ID is not set",conn);
    }
}
/*
 * Zeros object at id. It's possible that create can just call this
 * as in it's for loop
 */
void Database_delete(struct Connection *conn, int id)
{
    //TODO this might need to change to deal with the new structure
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

/*
 * Loop though the DB and if something is set print it
 */

void Database_list(struct Connection *conn)
{
    //TODO this might need to change to deal with the new structure
    int i = 0;
    struct Database *db = conn->db; //conn->db is a pointer to the DB

    for(i = 0; i < db->size; i++){
        //but db->rows[i] is an actual struct, hence the need for the &
        struct Address *cur = &db->rows[i]; 

        if (cur->set){
            Address_print(cur);
        }
    }
}

/*
 * Unified error logging and clean up
 */
void die(const char *message, struct Connection *conn)
{
    if(NULL != conn){
        Database_close(conn);
    }

    if (errno){ //if a system call fails, this value will be set
        perror(message); //this will print the error message to stderror
    } else {
        printf("ERROR: %s\n", message);
    }
    
    exit(1);
}

int main(int argc, char *argv[])
{
    //Minimum of 3 args required
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]",NULL);

    char *filename = argv[1]; //file name is first arg

    //First char of second string (persumalby rest is white space)
    char action = argv[2][0];

    struct Connection *conn = NULL;

    if ('c' == action){
        int max_rows = 0;
        int max_len = 0;
        if(argc != 5) {
            die("USAGE: ... c MAX_ROWS MAX_LEN",conn);
        } else {
            max_rows = atoi(argv[3]); 
            max_len = atoi(argv[4]); 
        }
        conn = Database_create(filename,max_rows,max_len);
        Database_write(conn);
    } else {
        //Create or open DB file
        conn = Database_open(filename);
        int id = 0;

        //if there is more than 3 args, the 4th entry in argv (which is the 
        //3rd arg) must be an id.
        if(argc > 3) id = atoi(argv[3]); 
    
        //TODO will have to handle this check differently.
        if(id >= conn->db->size) die("There's not that many reacords.",conn);

        //Dispatcher
        switch(action) {
            case 'g':
                if(argc != 4) die("USAGE: ... g ID",conn);

                Database_get(conn,id);
                break;

            case 's':
                if(argc != 6) die("USAGE: ... s ID NAME EMAIL",conn);

                Database_set(conn, id, argv[4], argv[5]);
                Database_write(conn);
                break;
            case 'd':
                if(argc != 4) die("USAGE: ... d ID",conn);

                Database_delete(conn,id);
                Database_write(conn);
                break;

            case 'l':
                Database_list(conn);
                break;

            default:
                die("Invalid action, only: c=create, g=get, s=set, d=del, l=list",conn);
        }
    }
    Database_close(conn); //cleanup

    return 0;

}
