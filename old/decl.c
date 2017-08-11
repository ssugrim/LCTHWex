#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

struct datapath{};
struct ofp_vport_action_pop_mpls{};
struct ofp_action_header{};
struct ofpbuf{};
struct sw_flow_key{};

uint16_t validate(struct datapath *dp,const struct ofp_action_header *ah){
    return 0;
};

void execute(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key, const struct ofp_action_header *ah){
};

struct openflow_vport_action {
    size_t min_size;
    size_t max_size;
    uint16_t (*validate)(struct datapath *dp, const struct ofp_action_header *ah);
    void (*execute)(struct datapath *dp, struct ofpbuf *buffer, const struct sw_flow_key *key, const struct ofp_action_header *ah);
};

struct openflow_vport_action * mk_vport_arr(){
    struct openflow_vport_action * vport_arr = malloc(sizeof(struct openflow_vport_action) * 4);

    vport_arr[0].min_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[0].max_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[0].validate = validate;
    vport_arr[0].execute = execute;

    vport_arr[1].min_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[1].max_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[1].validate = validate;
    vport_arr[1].execute = execute;

    vport_arr[2].min_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[2].max_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[2].validate = validate;
    vport_arr[2].execute = execute;

    vport_arr[3].min_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[3].max_size = sizeof(struct ofp_vport_action_pop_mpls);
    vport_arr[3].validate = validate;
    vport_arr[3].execute = execute;

    return vport_arr;
}

struct openflow_vport_action * port_arr = mk_vport_arr();

int main(){
    return 0;
}
