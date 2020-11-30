using System;
using System.Collections;
using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class SkeletalInterface : MonoBehaviour
{
	private UI_Animation ui;
	
	public int numNodesToInit;
	public int numStates;

	public Hierarchy hierarchy;

	// Base pose, flip through all, and clip-controlled.
	public List<HierarchyState> states;

	private void Awake()
	{
		ui = GetComponent<UI_Animation>();
		hierarchy = gameObject.AddComponent<Hierarchy>();
		states = new List<HierarchyState>();
	}

	private void Start()
	{
		hierarchy.Init(numNodesToInit);

		for (int i = 0; i < numStates; ++i)
		{
			HierarchyState tempState = new HierarchyState();

			tempState.Init(hierarchy);
			
			states.Add(tempState);
		}
	}

	private void Update()
	{
		// 1. Apply input from User
		// Acquire the value of the HierarchyState UI
		int stateController = ui.stateDrop.value;

		// 2. Update all Controllers

		// 3. Run the 4-step algorithm for each state
	}

	private void ApplyUserInput()
	{
		
	}

	private void UpdateControllers()
	{
		
	}

	private void KinematicAlgorithm()
	{
		for (int i = 0; i < states.Count; ++i)
		{
			states[i].UpdateState();
		}
	}
}