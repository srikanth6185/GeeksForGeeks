/*
 * Graph.c
 *
 *  Created on: Oct 16, 2017
 *      Author: srikanth
 */
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "Graph.h"
#include "Queue.h"
#include "Stack.h"

graph_t *create_graph(int vertices)
{
    graph_t *newG;

    if (vertices <= 0) {
        return NULL;
    }

    newG = (graph_t*)malloc(sizeof(graph_t));
    if (!newG) {
        return NULL;
    }
    memset(newG, 0, sizeof(graph_t));

    newG->vertices = vertices;

    newG->adj_arr = (adj_list_t*)malloc(sizeof(adj_list_t) * vertices);
    if (!newG->adj_arr) {
        free(newG);
        return NULL;
    }

    memset(newG->adj_arr, 0, sizeof(adj_list_t) * vertices);

    return newG;
}

void destroy_graph(graph_t *graph)
{
    if (!graph) {
        return;
    }

    /*Free the adj lists*/
    if (graph->vertices > 0) {
        int i;
        for(i = 0; i < graph->vertices; i++) {
            adj_node_t *curr = graph->adj_arr[i].head, *del;
            while(curr) {
                del = curr;
                curr = curr->next;
                free(del);
            }
        }

        free(graph->adj_arr);
    }

    /*Free main data structure*/
    free(graph);

    return;

}

int add_vertex(graph_t* graph, int v)
{
    return 0;
}

int add_edge(graph_t *graph, int v, int u, int bidirectional)
{
    adj_node_t* new_edge[2];

    if (!graph || (v < 0) || (u < 0) ||
        (v >= graph->vertices) || (u >= graph->vertices)) {
        return -1;
    }

    new_edge[0] = (adj_node_t*)malloc(sizeof(adj_node_t));
    if (NON_DIRECTIONAL == bidirectional) {
        new_edge[1] = (adj_node_t*)malloc(sizeof(adj_node_t));
    }

    if (!new_edge[0] || !new_edge[1]) {
        if (new_edge[0]) {
            free(new_edge[0]);
        }

        if (new_edge[1]) {
            free(new_edge[1]);
        }
        return -1;
    }

    new_edge[0]->dest = u;
    new_edge[0]->next = graph->adj_arr[v].head;
    graph->adj_arr[v].head = new_edge[0];

    if (NON_DIRECTIONAL == bidirectional) {
        new_edge[1]->dest = v;
        new_edge[1]->next = graph->adj_arr[u].head;
        graph->adj_arr[u].head = new_edge[1];
    }
    return 1;

}


void print_graph(graph_t *graph)
{
    if (!graph) {
        return;
    }

    if (graph->vertices) {
        int i;

        printf("No of vertices: %d\n", graph->vertices);
        for(i = 0; i < graph->vertices; i++) {
            adj_node_t *curr = graph->adj_arr[i].head;

            printf("Adj list for vertex: %d\n", i);

            while(curr) {
                printf("%d --> %d\n", i, curr->dest);
                curr = curr->next;
            }
        }
    }

    return;
}

void reset_visited(graph_t *g)
{
    int i = g->vertices - 1;

    for(;i >= 0; i--) {
        g->adj_arr[i].visited = 0;
    }
    return;
}

void bfs_traversal_graph(graph_t* graph, int v)
{
    q_t* q;
    adj_node_t* adj;

    if (!graph || graph->vertices <= 0 ||
        (v < 0) || (v > graph->vertices)) {
        printf("%s: BAD INPUT\n", __FUNCTION__);
        return;
    }

    reset_visited(graph);
    q = q_create();

    graph->adj_arr[v].visited = 1;
    en_q(q, NULL, v);

    while(!is_q_empty(q)) {
        de_q(q, NULL, &v);

        printf(" %d", v);

        adj = graph->adj_arr[v].head;
        while (adj) {
            if (!graph->adj_arr[adj->dest].visited) {
                en_q(q, NULL, adj->dest);
                graph->adj_arr[adj->dest].visited = 1;
            }
            adj = adj->next;
        }
    }

    printf("\n");

    q_destroy(q);

    return;
}

/* DFS traversal from the given vertex.
 * For disconnected graphs we can call the traversal
 * on all the vertices.
 * */
void dfs_traversal_graph(graph_t *graph, int v)
{
	st_t* st;
	adj_node_t* adj;

	printf("\n%s: START\n", __FUNCTION__);

	if (!graph || graph->vertices <= 0 ||
        (v < 0) || (v > graph->vertices)) {
        printf("%s: BAD INPUT\n", __FUNCTION__);
        return;
    }

    reset_visited(graph);
    st = st_create(VAL);
    st_push(st, v, NULL);

    while(!is_st_empty(st)) {
    	st_top(st, &v, NULL);
    	//Vertex not visited so visit.
    	if(!graph->adj_arr[v].visited) {
    		graph->adj_arr[v].visited = 1;
    		printf("%d ", v);
    	}

    	adj = graph->adj_arr[v].head;
    	while (adj) {
    		if (!graph->adj_arr[adj->dest].visited) {
    			st_push(st,adj->dest, NULL);
    			break;
    		}
    		adj = adj->next;
    	}
    	//All adj nodes visited
    	//Remove it from the stack
    	if (!adj) {
    		st_pop(st, &v, NULL);
    	}
    }

    printf("\n");
    st_destroy(st);
    return;
}


