using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MonsterMoveR : StateMachineBehaviour
{
    Monster monster;
    //OnStateEnter is called when a transition starts and the state machine starts to evaluate this state
    override public void OnStateEnter(Animator animator, AnimatorStateInfo stateInfo, int layerIndex)
    {
        monster = animator.gameObject.GetComponent<Monster>();
        monster.Move();
    }
}
