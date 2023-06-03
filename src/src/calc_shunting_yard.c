#include "calc_rpn/calc_deque.h"

static void process_operator(calc_deque_t* rpn, calc_deque_t* temp_stack,
                             calc_token_t* token) {
  bool is_processing_finished = false;

  while (temp_stack->size != 0 && is_processing_finished == false) {
    calc_token_t picked = deque_pick_back(temp_stack);
    is_processing_finished = true;

    if (picked.token_type == OPERATOR) {
      uint8_t on_stack_priority = picked.storage.operator.priority;
      uint8_t token_priority = token->storage.operator.priority;
      uint8_t token_association = token->storage.operator.association;

      if (on_stack_priority > token_priority ||
          (on_stack_priority == token_priority &&
           token_association == LEFT_ASSOCIATED)) {
        deque_push_back(rpn, picked);
        deque_pop_back(temp_stack);
        is_processing_finished = false;
      }
    }
  }
}

static void process_right_parenthesis(calc_deque_t* rpn,
                                      calc_deque_t* tmp_stack) {
  calc_token_t token = deque_pop_back(tmp_stack);

  while (token.token_type != LEFT_PARENTHESIS) {
    deque_push_back(rpn, token);
    token = deque_pop_back(tmp_stack);
  }

  token = deque_pick_back(tmp_stack);

  if (token.token_type == FUNCTION) {
    deque_push_back(rpn, token);
    deque_pop_back(tmp_stack);
  }
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
        deque_push_back(rpn, token);
        break;
      case FUNCTION:
      case LEFT_PARENTHESIS:
        deque_push_back(tmp_stack, token);
        break;
      case OPERATOR:
        process_operator(rpn, tmp_stack, &token);
        deque_push_back(tmp_stack, token);
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

  return rpn;
}
