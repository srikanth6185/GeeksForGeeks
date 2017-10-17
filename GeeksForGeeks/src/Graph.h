/*
 * Graph.h
 *
 *  Created on: Oct 16, 2017
 *      Author: srikanth
 */

#ifndef GRAPH_H_
#define GRAPH_H_

typedef struct adj_node_s {
	int dest;
	struct adj_node_s *next;
}adj_node_t;

/*Per vertex data and adj list.*/
typedef struct adj_list_s {
	void *data;
	adj_node_t *head;
}adj_list_t;


typedef struct graph_s {
	int vertices; /*Num of vertices in the graph*/
	adj_list_t *adj_arr; /*Array of pointers (size vertices)
	                       which gives the adjaceny of each
	                       vertex.*/
} graph_t;

#endif /* GRAPH_H_ */
