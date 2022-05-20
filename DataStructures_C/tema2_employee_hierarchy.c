#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hierarchy.h"

#define SIZE_OF_ARRAY 64

Tree get_Node(Tree tree, char *name)
{
    Tree aux;

    if (tree == NULL || name == NULL)
    {
        return NULL;
    }

    if (strcmp(tree->name, name) == 0)
    {
        return tree;
    }

    for (int i = 0; i < tree->direct_employees_no; i++)
    {
        aux = get_Node(tree->team[i], name);
        if (aux != NULL)
        {
            return aux;
        }
    }
    return NULL; //the case where we dont find the manager
}

Tree create_employee(char *employee_name, Tree manager)
{
    Tree employee = calloc(1, sizeof(TreeNode));
    employee->direct_employees_no = 0;
    employee->manager = manager;
    employee->name = employee_name;
    employee->team = NULL;
    return employee;
}

void rearrange_team(Tree *team, int team_size)
{
    if (team == NULL || team_size <= 1)
    {
        return;
    }
    Tree aux = NULL;
    for (int i = 0; i < team_size - 1; i++)
    {
        for (int j = i + 1; j < team_size; j++)
        {
            if (team[i] != NULL && team[j] != NULL)
            {
                //we lexicographically compare the 2 names if they are not NULL
                if (strcmp(team[i]->name, team[j]->name) > 0)
                {
                    aux = team[i];
                    team[i] = team[j];
                    team[j] = aux;
                }
            }
        }
    }
}

/* Adauga un angajat nou in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 * manager_name: numele sefului noului angajat
 *
 * return: intoarce ierarhia modificata. Daca tree si manager_name sunt NULL, 
           atunci employee_name e primul om din ierarhie.
 */
Tree hire(Tree tree, char *employee_name, char *manager_name)
{
    Tree employee, manager = get_Node(tree, manager_name), *aux = NULL;
    employee = create_employee(employee_name, manager);
    if (tree == NULL && manager_name == NULL)
    {
        return employee;
    }
    if (manager == NULL)
    {
        printf("Manager Error\n");
        return tree;
    }
    //here we handled all the particular cases

    //now the general case
    (manager->direct_employees_no)++;
    while (aux == NULL)
    {
        aux = realloc(manager->team,
            manager->direct_employees_no * sizeof(Tree));
    }
    manager->team = aux;
    manager->team[manager->direct_employees_no - 1] = employee;
    //we put employee into manager team and then rearranged it
    rearrange_team(manager->team, manager->direct_employees_no);
    return tree;
}

/* Sterge un angajat din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului concediat
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire(Tree tree, char *employee_name)
{
    if (tree == NULL)
    {
        return tree;
    }

    Tree employee = get_Node(tree, employee_name), *aux, boss;
    if (employee == NULL || employee->manager == NULL)
    {
        return tree;
    }
    //these 2 "if" loops represent the cases where I do nothing
    //just pass the tree as it already is

    if (employee->team != NULL)
    {
        //here we transfer employee's team to his manager team
        for (int i = 0; i < employee->direct_employees_no; i++)
        {
            aux = NULL;
            if (employee->team[i] != NULL)
            {
                employee->team[i]->manager = employee->manager;
                (employee->manager->direct_employees_no)++;
                while (aux == NULL)
                {
                    aux = realloc(employee->manager->team,
                        employee->manager->direct_employees_no * sizeof(Tree));
                }
                employee->manager->team = aux;
                employee->manager->team
                    [employee->manager->direct_employees_no - 1]
                        = employee->team[i];
            }
        }
    }

    //here we take out employee from a tree and free it's memory
    boss = employee->manager;
    for (int i = 0; i < boss->direct_employees_no; i++)
    {
        if (boss->team[i] == employee)
        {
            boss->team[i] = NULL;
            free(employee->team);
            free(employee);
        }
    }
    rearrange_team(employee->manager->team,
        employee->manager->direct_employees_no);
    return tree;
}

/* Promoveaza un angajat in ierarhie. Verifica faptul ca angajatul e cel putin 
 * pe nivelul 2 pentru a putea efectua operatia.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 *
 * return: intoarce ierarhia modificata.
 */
Tree promote(Tree tree, char *employee_name)
{
    Tree employee, boss, *aux;
    employee = get_Node(tree, employee_name);

    if (employee != NULL)
    {
        boss = employee->manager;
    }
    else
    {
        return tree;
    }
    if (boss != NULL)
    {
        if (boss->manager != NULL)
        {

            if (employee->team != NULL)
            {
                //here we transfer employee's team to his manager team
                for (int i = 0; i < employee->direct_employees_no; i++)
                {
                    aux = NULL;
                    if (employee->team[i] != NULL)
                    {
                        employee->team[i]->manager = boss;
                        (boss->direct_employees_no)++;
                        while (aux == NULL)
                        {
                            aux = realloc(boss->team,
                                boss->direct_employees_no * sizeof(Tree));
                        }
                        boss->team = aux;
                        boss->team[boss->direct_employees_no - 1]
                            = employee->team[i];
                    }
                }
            }

            //now we delete employee from his old manager
            for (int i = 0; i < boss->direct_employees_no; i++)
            {
                if (boss->team[i] == employee)
                {
                    boss->team[i] = NULL;
                }
            }
            rearrange_team(boss->team, boss->direct_employees_no);

            //now we transfer employee to his new manager
            employee->manager = boss->manager;
            employee->direct_employees_no = 0;
            free(employee->team);
            (boss->manager->direct_employees_no)++;
            aux = NULL;
            while (aux == NULL)
            {
                aux = realloc(boss->manager->team,
                    boss->manager->direct_employees_no * sizeof(Tree));
            }
            boss->manager->team = aux;
            boss->manager->team[boss->manager->direct_employees_no - 1]
                = employee;
            rearrange_team(boss->manager->team,
                boss->manager->direct_employees_no);
        }
    }
    return tree;
}

/* Muta un angajat in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_employee(Tree tree, char *employee_name, char *new_manager_name)
{
    if (tree == NULL || employee_name == NULL || new_manager_name == NULL)
    {
        return tree;
    }
    Tree employee, new_manager, boss, *aux;
    employee = get_Node(tree, employee_name);
    new_manager = get_Node(tree, new_manager_name);
    if (employee->manager == NULL || new_manager == NULL || employee == NULL)
    {
        return tree;
    }
    //these 2 "if" loops represent the cases where I just return the tree
    //(I do nothing)

    if (employee->manager == new_manager)
    {
        return tree;
    }

    boss = employee->manager;
    if (employee->team != NULL)
    {
        //here we transfer employee's team to his manager team
        for (int i = 0; i < employee->direct_employees_no; i++)
        {
            aux = NULL;
            if (employee->team[i] != NULL)
            {
                employee->team[i]->manager = boss;
                (boss->direct_employees_no)++;
                while (aux == NULL)
                {
                    aux = realloc(boss->team,
                        boss->direct_employees_no * sizeof(Tree));
                }
                boss->team = aux;
                boss->team[boss->direct_employees_no - 1]
                    = employee->team[i];
            }
        }
    }

    //now we delete employee from his old manager
    for (int i = 0; i < boss->direct_employees_no; i++)
    {
        if (boss->team[i] == employee)
        {
            boss->team[i] = NULL;
        }
    }
    rearrange_team(boss->team, boss->direct_employees_no);

    for (int i = 0; i < employee->direct_employees_no; i++)
    {
        employee->team[i] = NULL;
    }

    //now we transfer employee to his new manager
    employee->manager = new_manager;
    (new_manager->direct_employees_no)++;
    aux = NULL;
    while (aux == NULL)
    {
        aux = realloc(new_manager->team,
            new_manager->direct_employees_no * sizeof(Tree));
    }
    new_manager->team = aux;
    new_manager->team[new_manager->direct_employees_no - 1] = employee;
    rearrange_team(new_manager->team, new_manager->direct_employees_no);

    return tree;
}

/* Muta o echipa in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei mutate
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_team(Tree tree, char *employee_name, char *new_manager_name)
{
    Tree employee, new_manager, boss, *aux = NULL;
    employee = get_Node(tree, employee_name);
    new_manager = get_Node(tree, new_manager_name);

    if (tree == NULL || employee->manager == NULL)
    {
        return tree;
    }
    if (employee == NULL || new_manager == NULL)
    {
        return tree;
    }
    if (employee->manager == new_manager)
    {
        return tree;
    }
    //this "if" loops represent the cases where I should do nothing
    //so I just return the TREE as it is

    //now I delete employee from his manager team
    boss = employee->manager;
    for (int i = 0; i < boss->direct_employees_no; i++)
    {
        if (boss->team[i] == employee)
        {
            boss->team[i] = NULL;
        }
    }
    rearrange_team(boss->team, boss->direct_employees_no);

    //now we transfer employee to his new manager
    employee->manager = new_manager;
    (new_manager->direct_employees_no)++;
    while (aux == NULL)
    {
        aux = realloc(new_manager->team,
            new_manager->direct_employees_no * sizeof(Tree));
    }
    new_manager->team = aux;
    new_manager->team[new_manager->direct_employees_no - 1] = employee;
    rearrange_team(new_manager->team, new_manager->direct_employees_no);
    return tree;
}

/* Concediaza o echipa din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei concediate
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire_team(Tree tree, char *employee_name)
{
    Tree boss, employee = get_Node(tree, employee_name);
    if (employee == NULL)
    {
        return tree;
    }
    else if (employee->manager == NULL)
    {
        return tree;
    }
    //this "if" loops represent the cases where I should do nothing
    //so I just return the TREE as it is

    //now I delete employee from his manager team
    boss = employee->manager;
    for (int i = 0; i < boss->direct_employees_no; i++)
    {
        if (boss->team[i] == employee)
        {
            boss->team[i] = NULL;
        }
    }
    rearrange_team(boss->team, boss->direct_employees_no);
    employee->manager = NULL;

    //we just free the memory for employee and all of his employees
    destroy_tree(employee);

    return tree;
}

int get_node_lvl(Tree tree, Tree employee)
{   
    int lvl = 0;
    Tree node = employee;
    while (node->manager != NULL) {
        node = node->manager;
        lvl++;
    }
    return lvl;
}

/* Reorganizarea ierarhiei cu un alt angajat in varful ierarhiei.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului care trece in varful ierarhiei
 */
Tree reorganize(Tree tree, char *employee_name)
{
    return tree;
}

void print_tree(FILE *f, Tree tree)
{
    if (tree != NULL)
    {
        if (tree->manager == NULL)
        {
            fprintf(f, "%s ", tree->name);
        }
        else
        {
            fprintf(f, "%s-%s ", tree->name, tree->manager->name);
        }
        for (int i = 0; i < tree->direct_employees_no; i++)
        {
            print_tree(f, tree->team[i]);
        }
    }
}

/* Parcurge ierarhia conform parcurgerii preordine.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */
void preorder_traversal(FILE *f, Tree tree)
{
    print_tree(f, tree);
    fprintf(f, "\n");
    //we use this to add "\n" at the end of the text
    return;
}

/* Elibereaza memoria alocata nodurilor din arbore
 *
 * tree: ierarhia existenta
 */
void destroy_tree(Tree tree)
{
    if (tree != NULL)
    {
        if (tree->direct_employees_no == 0)
        {
            //case where we got leaf_node
            free(tree);
        }
        else
        {   //we use function on node's employees
            for (int i = 0; i < tree->direct_employees_no; i++)
            {
                destroy_tree(tree->team[i]);
            }
            free(tree->team);
            free(tree);
        }
    }
}
