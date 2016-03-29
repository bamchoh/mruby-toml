/*
** mrb_toml.c - Toml class
**
** Copyright (c) bamchoh 2016
**
** See Copyright Notice in LICENSE
*/

#include "mruby.h"
#include "mruby/data.h"
#include "mruby/array.h"
#include "mruby/hash.h"
#include "mrb_toml.h"

#include "stdlib.h"
#include "errno.h"
#include "string.h"

#include "toml.h"
#include "toml_private.h"
#include "ccan/list/list.h"

#define DONE mrb_gc_arena_restore(mrb, 0);

typedef struct {
  char *str;
  int len;
} mrb_toml_data;

static const struct mrb_data_type mrb_toml_data_type = {
  "mrb_toml_data", mrb_free,
};

static mrb_value mrb_toml_init(mrb_state *mrb, mrb_value self)
{
  mrb_toml_data *data;
  char *str;
  int len;

  data = (mrb_toml_data *)DATA_PTR(self);
  if (data) {
    mrb_free(mrb, data);
  }
  DATA_TYPE(self) = &mrb_toml_data_type;
  DATA_PTR(self) = NULL;

  mrb_get_args(mrb, "s", &str, &len);
  data = (mrb_toml_data *)mrb_malloc(mrb, sizeof(mrb_toml_data));
  data->str = str;
  data->len = len;
  DATA_PTR(self) = data;

  return self;
}

static mrb_value toml_value_to_mrb_value(mrb_state* mrb, struct toml_node *node) {
  mrb_value ret;
  switch(node->type) {
    case TOML_ROOT:
      {
        struct toml_table_item *item = NULL;
        mrb_value hash = mrb_hash_new(mrb);
        list_for_each(&node->value.map, item, map) {
          int ai = mrb_gc_arena_save(mrb);
          mrb_value key = mrb_str_new_cstr(mrb, (&item->node)->name);
          mrb_value val = toml_value_to_mrb_value(mrb, &item->node);
          mrb_hash_set(mrb, hash, key, val);
          mrb_gc_arena_restore(mrb, ai);
        }
        ret = hash;
      }
      break;
    case TOML_BOOLEAN:
      if(node->value.integer) {
        ret = mrb_true_value();
      } else {
        ret = mrb_false_value();
      }
      break;
    case TOML_INT: 
      ret = mrb_fixnum_value((mrb_int)node->value.integer);
      break;
    case TOML_FLOAT:
      ret = mrb_float_value(mrb, node->value.floating.value);
      break;
    case TOML_STRING:
      ret = mrb_str_new_cstr(mrb, node->value.string);
      break;
    case TOML_TABLE:
      {
        struct toml_table_item *item = NULL;
        mrb_value hash = mrb_hash_new(mrb);
        list_for_each(&node->value.map, item, map) {
          int ai = mrb_gc_arena_save(mrb);
          mrb_value key = mrb_str_new_cstr(mrb, (&item->node)->name);
          mrb_value val = toml_value_to_mrb_value(mrb, &item->node);
          mrb_hash_set(mrb, hash, key, val);
          mrb_gc_arena_restore(mrb, ai);
        }
        ret = hash;
      }
      break;
    case TOML_LIST:
    case TOML_TABLE_ARRAY:
      {
        struct toml_list_item *item = NULL;
        mrb_value ary = mrb_ary_new(mrb);
        list_for_each(&node->value.list, item, list) {
          int ai = mrb_gc_arena_save(mrb);
          mrb_ary_push(mrb, ary, toml_value_to_mrb_value(mrb, &item->node));
          mrb_gc_arena_restore(mrb, ai);
        }
        ret = ary;
      }
      break;
    case TOML_DATE:
    default:
      ret = mrb_nil_value();
      break;
  }
  return ret;
}

static mrb_value mrb_toml_parse(mrb_state *mrb, mrb_value self)
{
  char *buf;
  int len, ret;
  struct toml_node *root;
  mrb_value value;
  mrb_get_args(mrb, "s", &buf, &len);

  ret = toml_init(&root);
  if(ret == -1) {
    mrb_raisef(mrb, E_RUNTIME_ERROR, "toml_init error: %S", strerror(errno));
  }

  ret = toml_parse(root, buf, len);
  if(ret) {
    toml_free(root);
    mrb_raise(mrb, E_RUNTIME_ERROR, "toml_parse error");
  }

  value = toml_value_to_mrb_value(mrb, root);

  toml_free(root);

  return value;
}

void mrb_mruby_toml_gem_init(mrb_state *mrb)
{
  struct RClass *toml;
  toml = mrb_define_class(mrb, "Toml", mrb->object_class);
  mrb_define_method(mrb, toml, "initialize", mrb_toml_init, MRB_ARGS_REQ(1));
  mrb_define_class_method(mrb, toml, "parse", mrb_toml_parse, MRB_ARGS_REQ(1));
  DONE;
}

void mrb_mruby_toml_gem_final(mrb_state *mrb)
{
}

