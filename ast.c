#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include "pogo_types.h"
#include "data_loader.h"

FilterNode* create_logic_node(NodeType type, FilterNode *left, FilterNode *right) {
    FilterNode *node = (FilterNode*)malloc(sizeof(FilterNode));
    if (!node) {
        fprintf(stderr, "Bellek hatasi\n");
        exit(1);
    }
    node->type = type;
    node->left = left;
    node->right = right;
    node->min_val = 0;
    node->max_val = 0;
    node->string_val[0] = '\0';
    return node;
}

FilterNode* create_range_node(NodeType type, int min_val, int max_val) {
    FilterNode *node = (FilterNode*)malloc(sizeof(FilterNode));
    if (!node) {
        fprintf(stderr, "Bellek hatasi\n");
        exit(1);
    }
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->min_val = min_val;
    node->max_val = max_val;
    node->string_val[0] = '\0';
    return node;
}

FilterNode* create_string_node(NodeType type, const char *str) {
    FilterNode *node = (FilterNode*)malloc(sizeof(FilterNode));
    if (!node) {
        fprintf(stderr, "Bellek hatasi\n");
        exit(1);
    }
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->min_val = 0;
    node->max_val = 0;
    if (str) {
        strncpy(node->string_val, str, sizeof(node->string_val) - 1);
        node->string_val[sizeof(node->string_val) - 1] = '\0';
    } else {
        node->string_val[0] = '\0';
    }
    return node;
}

FilterNode* create_int_node(NodeType type, int val) {
    FilterNode *node = (FilterNode*)malloc(sizeof(FilterNode));
    if (!node) {
        fprintf(stderr, "Bellek hatasi\n");
        exit(1);
    }
    node->type = type;
    node->left = NULL;
    node->right = NULL;
    node->min_val = val;
    node->max_val = val;
    node->string_val[0] = '\0';
    return node;
}

void free_ast(FilterNode *root) {
    if (!root) return;
    free_ast(root->left);
    free_ast(root->right);
    free(root);
}

bool evaluate_pokemon(const PokemonInstance *inst, const PokemonBase *base, const FilterNode *root) {
    if (!root) return true;

    switch (root->type) {
        case NODE_AND:
            return evaluate_pokemon(inst, base, root->left) && evaluate_pokemon(inst, base, root->right);

        case NODE_OR:
            return evaluate_pokemon(inst, base, root->left) || evaluate_pokemon(inst, base, root->right);

        case NODE_NOT:
            return !evaluate_pokemon(inst, base, root->left);

        case NODE_CP_RANGE:
            return (inst->cp >= root->min_val && inst->cp <= root->max_val);

        case NODE_HP_RANGE:
            return (inst->hp >= root->min_val && inst->hp <= root->max_val);

        case NODE_AGE_RANGE:
            return (inst->catch_days_ago >= root->min_val && inst->catch_days_ago <= root->max_val);

        case NODE_YEAR_RANGE:
            return (inst->catch_year >= root->min_val && inst->catch_year <= root->max_val);

        case NODE_ID_RANGE:
            return (inst->poke_id >= root->min_val && inst->poke_id <= root->max_val);

        case NODE_IV_STAR: {
            int iv_total = inst->iv_attack + inst->iv_defense + inst->iv_hp;
            int star = 0;
            if (iv_total >= 0 && iv_total <= 22) star = 0;
            else if (iv_total >= 23 && iv_total <= 29) star = 1;
            else if (iv_total >= 30 && iv_total <= 36) star = 2;
            else if (iv_total >= 37 && iv_total <= 44) star = 3;
            else if (iv_total == 45) star = 4;
            return (star == root->min_val);
        }

        case NODE_STRING_MATCH: {
            if (root->string_val[0] == '@') {
                const char *m = root->string_val + 1;
                // Yeteneklerde (move) tam eslesme (strcasecmp)
                if (inst->move1 && strcasecmp(inst->move1, m) == 0) return true;
                if (inst->move2 && strcasecmp(inst->move2, m) == 0) return true;
                if (inst->move1_type && strcasecmp(inst->move1_type, m) == 0) return true;
                if (inst->move2_type && strcasecmp(inst->move2_type, m) == 0) return true;
                return false;
            } else {
                if (base->type1 && strcasecmp(base->type1, root->string_val) == 0) return true;
                if (base->type2 && strcasecmp(base->type2, root->string_val) == 0) return true;
                // Sadece Pokemon isimlerinde alt dizi (strcasestr)
                if (base->name && strcasestr(base->name, root->string_val) != NULL) return true;
                return false;
            }
        }

        case NODE_WEAK_TO: {
            int m1 = base->type1 ? get_type_multiplier(root->string_val, base->type1) : 100;
            int m2 = base->type2 ? get_type_multiplier(root->string_val, base->type2) : 100;
            return ((m1 * m2) / 100 > 100);
        }

        case NODE_STRONG_AGAINST: {
            int m1 = inst->move1_type ? get_type_multiplier(inst->move1_type, root->string_val) : 100;
            int m2 = inst->move2_type ? get_type_multiplier(inst->move2_type, root->string_val) : 100;
            return (m1 > 100 || m2 > 100);
        }

        case NODE_BOOL_FLAG: {
            if (strcasecmp(root->string_val, "shiny") == 0) return inst->is_shiny;
            if (strcasecmp(root->string_val, "shadow") == 0) return inst->is_shadow;
            if (strcasecmp(root->string_val, "legendary") == 0) return base->is_legendary;
            if (strcasecmp(root->string_val, "mythical") == 0) return base->is_mythical;
            if (strcasecmp(root->string_val, "evolve") == 0) return (base->candy_to_evolve > 0 && inst->candy_count >= base->candy_to_evolve);
            return false;
        }

        default:
            return false;
    }
}
