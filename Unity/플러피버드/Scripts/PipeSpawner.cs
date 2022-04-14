using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PipeSpawner : MonoBehaviour
{
    public GameObject pipe;

    public float spawnDistance = 5;
    public float spawnDelay = 2;

    public float randomRange = 1;

    float random;
    // Start is called before the first frame update
    private void OnEnable()
    {
        Invoke("SpawnPipe", spawnDelay);
    }
    private void OnDisable()
    {
        CancelInvoke("SpawnPipe");
    }
    private void SpawnPipe()
    {
        random = Random.Range(-randomRange, randomRange);

        Instantiate(pipe, new Vector2(spawnDistance, random), Quaternion.identity);

        Invoke("SpawnPipe", spawnDelay);
    }
}
