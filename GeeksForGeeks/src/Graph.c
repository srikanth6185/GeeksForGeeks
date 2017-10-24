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

int add_edge(graph_t *graph, int v, int u, int bidirectional, int weight)
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
    new_edge[0]->weight = weight;
    new_edge[0]->next = graph->adj_arr[v].head;
    graph->adj_arr[v].head = new_edge[0];


    if (NON_DIRECTIONAL == bidirectional) {
        new_edge[1]->dest = v;
        new_edge[1]->weight = weight;
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
    printf("\n")
;    return;
}

void reset_visited(graph_t *g)
{
    int i = g->vertices - 1;

    for(;i >= 0; i--) {
        g->adj_arr[i].visited = 0;
        g->adj_arr[i].dist = NEG_INFINITY;
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

/* Fill the stack with reverse DFS
 * */
void topological_sort_util(graph_t* graph, int v, st_t *st)
{
    adj_node_t *adj = graph->adj_arr[v].head;
    graph->adj_arr[v].visited = 1;

    while(adj) {
        if (!graph->adj_arr[adj->dest].visited) {
            topological_sort_util(graph, adj->dest, st);
        }
        adj = adj->next;
    }

    st_push(st, v, NULL);
}

void topological_sort_graph(graph_t* graph)
{
    st_t *st;
    int idx, vertex;

    if (!graph) {
        printf("%s: BAD INPUT\n", __FUNCTION__);
        return;
    }

    st = st_create(VAL);
    reset_visited(graph);

    for(idx = 0; idx < graph->vertices; idx++) {
    		if (!graph->adj_arr[idx].visited) {
    			topological_sort_util(graph, idx, st);
        }
    }

    printf("Topological ordering: ");
    while (!is_st_empty(st)) {
        st_pop(st, &vertex, NULL);
        printf("%d ", vertex);
    }

    st_destroy(st);
    return;
}

void lonest_path_directed_acyclic_graph(graph_t *graph, int src)
{
    st_t *st;
    int idx, vertex;

    if (!graph || (src < 0) || (src > graph->vertices)) {
        printf("%s: BAD INPUT\n", __FUNCTION__);
        return;
    }

    st = st_create(VAL);
    reset_visited(graph);

    /* Set the distance of the src to
     * zero.*/
    graph->adj_arr[src].dist = 0;

    /* Prep the stack with DFS walk of the nodes.
     * AKA topological sort.
     * Note:
     * I think we can do this only for the source vertex.
     * I have not seen any evidence to the contrary.
     * Again assuming that we need longest path only for
     * the src node to all other nodes.
     *
     * O(V+E)
     * */
    for(idx = 0; idx < graph->vertices; idx++) {
		if (!graph->adj_arr[idx].visited) {
			topological_sort_util(graph, src, st);
		}
    }

    while (!is_st_empty(st)) {
		adj_node_t *adj;
		st_pop(st, &vertex, NULL);
		adj = graph->adj_arr[vertex].head;

		if (graph->adj_arr[vertex].dist != NEG_INFINITY) {
			/*Walk each adjacent vertex and update the distance if its less.*/
			while (adj) {
				if (graph->adj_arr[adj->dest].dist < (graph->adj_arr[vertex].dist + adj->weight)) {
					graph->adj_arr[adj->dest].dist = graph->adj_arr[vertex].dist + adj->weight;
				}
				adj = adj->next;
			}
		}
    }

    for(idx = 0; idx < graph->vertices; idx++) {
    	if (graph->adj_arr[idx].dist != NEG_INFINITY) {
    		printf("vertex: %d dist: %d\n", idx, graph->adj_arr[idx].dist);
    	}
    }

    st_destroy(st);
    return;
}


void DFSUtil(graph_t *graph, int vertex)
{
	adj_node_t *adj = graph->adj_arr[vertex].head;
	graph->adj_arr[vertex].visited = 1;

	while(adj) {
		if (!graph->adj_arr[adj->dest].visited) {
			DFSUtil(graph, adj->dest);
		}
		adj = adj->next;
	}
}

/* Finding mother vertex.
 *
 * Perform DFS on all vertices.
 * Store the vertex that was traversed last.
 * That v must be the mother vertex.
 * Return -1 if not.
 *
 * Koseraju's algorithm
 * Applicable to Directed connected graph only
 *
 * Undirected connected - Every vertex is a mother vertex.
 * Undirected/Directed Disconnected - No mother vertex.
 *                                    All nodes are not reachable
 * */
int find_mother_vertex_in_graph(graph_t* graph, int* mother_vertex)
{
	int idx, v;

	if (!graph || !mother_vertex || !graph->vertices) {
		return -1;
	}

	reset_visited(graph);

	for(idx = 0; idx < graph->vertices; idx++) {
		if (!graph->adj_arr[idx].visited) {
			DFSUtil(graph, idx);
			v = idx;
		}
	}

	reset_visited(graph);
	DFSUtil(graph, v);

	for(idx = 0; idx < graph->vertices; idx++) {
		if (!graph->adj_arr[idx].visited) {
			printf("No Mother vertex found \n");
			return -1;
		}
	}

	*mother_vertex = v;
	printf("Mother vertex: %d \n", v);
	return 1;

}
