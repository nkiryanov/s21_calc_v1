#include "calc_rpn/calc_deque.h"

static void move_from_stack_if_token_type(calc_deque_t* rpn,
                                          calc_deque_t* tmp_stack,
                                          enum TOKEN_TYPE expected_token_type) {
  // Check if `tmp_stack` has token of specified type.
  // If so push it to rpn

  if (tmp_stack->size != 0) {
    calc_token_t picked = deque_pick_back(tmp_stack);

    if (picked.token_type == expected_token_type) {
      deque_push_back(rpn, picked);
      deque_pop_back(tmp_stack);
    }
  }
}

static void process_binary_operator(calc_deque_t* rpn, calc_deque_t* tmp_stack,
                                    calc_token_t token) {
  bool is_processing_finished = false;

  while (tmp_stack->size != 0 && is_processing_finished == false) {
    calc_token_t picked = deque_pick_back(tmp_stack);
    is_processing_finished = true;

    if (picked.token_type == BINARY_OPERATOR) {
      uint8_t on_stack_priority = picked.storage.operator.priority;
      uint8_t token_priority = token.storage.operator.priority;
      uint8_t token_association = token.storage.operator.association;

      if (on_stack_priority > token_priority ||
          (on_stack_priority == token_priority &&
           token_association == LEFT_ASSOCIATED)) {
        deque_push_back(rpn, picked);
        deque_pop_back(tmp_stack);
        is_processing_finished = false;
      }
    }
  }

  deque_push_back(tmp_stack, token);
}

static void process_right_parenthesis(calc_deque_t* rpn,
                                      calc_deque_t* tmp_stack) {
  calc_token_t token = deque_pop_back(tmp_stack);

  while (token.token_type != LEFT_PARENTHESIS) {
    deque_push_back(rpn, token);
    token = deque_pop_back(tmp_stack);
  }

  move_from_stack_if_token_type(rpn, tmp_stack, FUNCTION);
  move_from_stack_if_token_type(rpn, tmp_stack, UNARY_OPERATOR);
}

calc_deque_t* do_shunting_yard(calc_deque_t* math_tokens) {
  // Return expression in RPN (reverse polish notation)
  // The function expected that the `math_expression` is valid

  calc_deque_t* rpn = deque_init();  // Aka Revers Polish Notation
  calc_deque_t* tmp_stack = deque_init();

  while (math_tokens->size != 0) {
    calc_token_t token = deque_pop_front(math_tokens);

    switch (token.token_type) {
      case NUMBER:
      case X_VARIABLE:
        deque_push_back(rpn, token);
        move_from_stack_if_token_type(rpn, tmp_stack, UNARY_OPERATOR);
        break;
      case FUNCTION:
      case LEFT_PARENTHESIS:
      case UNARY_OPERATOR:
        deque_push_back(tmp_stack, token);
        break;
      case BINARY_OPERATOR:
        process_binary_operator(rpn, tmp_stack, token);
        break;
      case RIGHT_PARENTHESIS:
        process_right_parenthesis(rpn, tmp_stack);
        break;
      default:
        break;
    }
  }

  while (tmp_stack->size != 0) {
    deque_push_back(rpn, deque_pop_back(tmp_stack));
  }

  deque_destroy(&tmp_stack);

  return rpn;
}
